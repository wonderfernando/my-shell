#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

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

}

int main(int ac, char **av, char **env)
{
	char	*script;
    t_data data;

	load_var(&data, env); 
	printf("%s\n", get_env_value(&data, "USER"));
    while (1) {
        char *script = readline("digite a linha: ");
        add_history(script);
        free(script);
    }
    return 0;
}
