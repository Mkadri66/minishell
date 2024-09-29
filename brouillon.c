/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:10:55 by momillio          #+#    #+#             */
/*   Updated: 2024/09/04 16:51:02 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char whitespace [] = " \t\r\n\v";
char symbols [] = "<|>&;()";

int	get_token (char **ps, char *es, char **q, char **eq)
{
	char *s;
	int ret;

	s = *ps;
	while (s < es && strchr (whitespace, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	switch (*s)
	{
		case 0;
			break ;
		case '|':
		case '(':
		case ')':
		case ';':
		case '&':
		case '<':
			s++;
			break ;
		case '>':
			s++;
			if (*s == '>')
			{
				ret = '+';
				s++
			}
			break ;
	}
	default: // si ce n'est aucun des cas précédents 
		ret = 'a';
		while ((s < es && !strchr(whitespace, *s) && !strchr (symbols, *s)))
			s++;
		break ;
	if (eq)
		*eq = s;	
	while (s < es && strchr (whitespace, *s))
		s++;
	*ps = s;
	return (ret); 
}

int peek (char **ps, char *es, char *c)
{
	char *s;

	s = *ps;
	while (s < es && strchr (whitespace, *s))
		s++;
	*ps = s;
	return (*s && strchr (c, *s));
}

struct cmd *parsecmd (char *s)
{
	char *es;
	struct cmd *cmd;
	es = s + strlen (s); // ptr to \0
	cmd = parseline (&s, es); 
	peek (&s, es, ""); // vérifie qu'on soit bien à la fin de la string
	if (s != es)
		error ;
	nulterminate (cmd); // mets un \0 à la fin de la str 
	return (cmd);
}

struct cmd *parsepipe (char **ps, char *es)
{
	struct cmd *cmd;

	cmd = parseexec (ps, es);
	if (peek (ps, es, "|"))
	{
		get_token (ps, es, 0, 0);
		cmd = pipecmd (cmd, parsepipe (ps, es));
	}
	return (cmd);
}

struct cmd *parseredirs (struct cmd *cmd, char **ps, char *es)
{
	int tok;
	char *q;
	char *eq;

	while (peek (ps, es, "<>"))
	{
		tok = get_token (ps, es, 0, 0);
		if (get_token (ps, es, &q, &eq) != 'a')
			error ("missing file");
		switch (tok)
		{
			case '<':
				cmd = redircmd (cmd, q, eq, O_RDONLY, 0);
				break;
			case '>':
				cmd = redircmd (cmd, q, eq, O_WRONLY | O_CREATE | O_TRUNC, 1);
				break;
			case '+': // >>
				cmd = redircmd (cmd, q, eq, O_WRONLY | O_CREATE, 1);
				break;
		}
	}
	return (cmd);
}

struct cmd *parseexec (char **ps, char *es)
{
	char *q;
	char *eq;
	int tok;
	int argc;
	struct execcmd *cmd;
	struct cmd *ret;

	ret = execcmd (); // allocate the note
	cmd  = (struct execcmd*) ret;
	argc = 0;
	ret = parseredirs (ret, ps, es);
	while (!peek (ps, es, "|)&;"))
	{
		if ((tok = get_token (ps, es, &q, &eq)) == 0)
			break;
		if (tok != 'a')
			error ("syntax");
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		if (argc >= MAX_ARGS)
			error ("too many args");
		ret = parseredirs (ret, ps, es);
	}
	cmd->argv[argc] = 0; // nulterminate the array
	cmd->eargv[argc] = 0; // nulterminate the array
	return (ret);
}