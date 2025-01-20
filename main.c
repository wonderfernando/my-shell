#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
/* Split*/


size_t	ft_strlen(const char *s)
{
	size_t l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}
static int	count_words(const char *str, char c)
{
	int i;
	int trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
    
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];

	word[i] = '\0';

	return (word);
}

char		**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	if (!s || !(split = malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

///////




typedef struct s_env {
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_data {
    t_env *envs;  // Lista encadeada para armazenar variáveis de ambiente
} t_data;

void load_var(t_data *data, char **env)
{
    t_env *new_env;
    t_env *head = NULL;  // Inicializa a cabeça da lista como NULL
    t_env *list = NULL;  // Ponteiro auxiliar para manter o final da lista
    char **cp = env;     // Ponteiro para percorrer o array de strings 'env'

    while (*cp != NULL)
    { 
        // Criação de um novo nó
        new_env = malloc(sizeof(t_env));
        if (!new_env) {
            perror("malloc");
            return;
        }

        new_env->value = *cp;  // Armazena o valor da variável de ambiente
        new_env->next = NULL;   // O próximo nó será NULL (último nó da lista)

        if (head == NULL)
            head = new_env;  // Se a lista está vazia, o novo nó é o primeiro
        else
            list->next = new_env;  // Caso contrário, adiciona o novo nó no final

        list = new_env;  // Atualiza o ponteiro 'list' para o novo nó
        cp++;  // Avança para a próxima variável de ambiente
    }

    data->envs = head;  // Atribui a lista criada à variável de ambiente de 'data'
}

char* get_env_value(t_data *data, const char *var_name) {
    t_env *current = data->envs;
    size_t var_name_len = strlen(var_name);

    while (current != NULL) {
        if (strncmp(current->value, var_name, var_name_len) == 0 && current->value[var_name_len] == '=') {
            return current->value + var_name_len + 1;  // Retorna o valor após o '='
        }
        current = current->next;
    }
    return NULL;  // Caso a variável não seja encontrada
}

char	*expand_variable(char *str)
{
    char *first = strchr(str, '"');
    if (first == NULL)
        return str;
    char **div = ft_split(str,' ');
    
    while (*div!=NULL)
    {
        if (*div[0] == '$')
        {
            
        }
        div++;
    } 
    return str;
    //ola todo mundo $USER eu sou $HOME
}

int main(int ac, char **av, char **env)
{
	char	*script;
    t_data data;

	load_var(&data, env); 
	//printf("%s\n", get_env_value(&data, "USER"));
    while (1) {
        char *script = readline("digite a linha: ");
        expand_variable(script);
        add_history(script);
        free(script);
    }
    return 0;
}
