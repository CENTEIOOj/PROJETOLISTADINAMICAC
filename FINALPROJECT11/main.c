#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Definição da struct para armazenar dados da obra de arte
typedef struct ObraDeArte {
    char titulo[101]; // Título da obra de arte
    char artista[51]; // Nome do artista responsável pela obra
    char tipo[20]; // Tipo da obra (pintura, escultura, fotografia, etc.)
    int ano; // Ano de criação da obra
    float preco; // Preço da obra
    int dimensao_largura; // Largura da obra
    int dimensao_altura; // Altura da obra
    int dimensao_profundidade; // Profundidade da obra
    int dimensao_peso; // Peso da obra
    char localizacao[51]; // Localização atual da obra
    char estado[20]; // Estado atual da obra (vendida, para venda, etc.)
    int classificacao; // Classificação da obra (de 0 a 5)
    char notas[301]; // Notas adicionais sobre a obra
    struct ObraDeArte *proximo; // Ponteiro para o próximo elemento da lista encadeada
} ObraDeArte;

// Declarações das funções de validação
int validarArtista(char *artista); // Função para validar o nome do artista
int validarTipoObra(char *tipo); // Função para validar o tipo da obra
int validarAno(int ano); // Função para validar o ano da obra
int validarPreco(float preco); // Função para validar o preço da obra
int validarDimensoes(int largura, int altura, int profundidade, int peso); // Função para validar as dimensões da obra
int validarLocalizacao(char *localizacao); // Função para validar a localização da obra
int validarEstado(char *estado); // Função para validar o estado da obra
int validarClassificacao(int classificacao); // Função para validar a classificação da obra

// Função para criar uma nova obra de arte (aloca memória)
ObraDeArte *criarObraDeArte() {
    ObraDeArte *novaObra = (ObraDeArte *)malloc(sizeof(ObraDeArte)); // Aloca memória para uma nova obra
    if (novaObra == NULL) { // Verifica se a alocação foi bem-sucedida
        printf("Erro ao alocar memória para a obra de arte.\n");
        return NULL;
    }
    novaObra->proximo = NULL; // Inicializa o ponteiro para o próximo elemento como NULL
    return novaObra; // Retorna o ponteiro para a nova obra
}

// Função para liberar a memória de uma obra de arte
void liberarObraDeArte(ObraDeArte *obra) {
    if (obra != NULL) {
        free(obra); // Libera a memória alocada para a obra de arte
    }
}

// Função para inserir uma obra de arte na lista encadeada
void inserirObraDeArte(ObraDeArte **lista, ObraDeArte *novaObra) {
    if (novaObra == NULL) {
        return;
    }

    novaObra->proximo = *lista; // Define o próximo da nova obra como o primeiro elemento da lista
    *lista = novaObra; // Atualiza a cabeça da lista para a nova obra
}

// Função para buscar uma obra de arte na lista encadeada
ObraDeArte *procurarObraDeArte(ObraDeArte *lista, char *termoProcura, char *campoProcura) {
    while (lista != NULL) {
        if (strcmp(campoProcura, "titulo") == 0 && strcmp(lista->titulo, termoProcura) == 0) {
            return lista;
        } else if (strcmp(campoProcura, "artista") == 0 && strcmp(lista->artista, termoProcura) == 0) {
            return lista;
        } else if (strcmp(campoProcura, "tipo") == 0 && strcmp(lista->tipo, termoProcura) == 0) {
            return lista;
        } else if (strcmp(campoProcura, "estado") == 0 && strcmp(lista->estado, termoProcura) == 0) {
            return lista;
        } else if (strcmp(campoProcura, "localizacao") == 0 && strcmp(lista->localizacao, termoProcura) == 0) {
            return lista;
        }
        lista = lista->proximo;
    }
    return NULL; // Retorna NULL se a obra não for encontrada
}

// Função para validar artista
int validarArtista(char *artista) {
    for (int i = 0; artista[i] != '\0'; i++) {
        if (!isalpha(artista[i]) && !isspace(artista[i])) {
            return 0; // Retorna 0 se o nome do artista contiver caracteres inválidos
        }
    }
    return 1; // Retorna 1 se o nome do artista for válido
}

// Função para validar tipo de obra
int validarTipoObra(char *tipo) {
    const char *tiposValidos[] = {"pintura", "escultura", "fotografia", "outro"}; // Tipos válidos de obras
    for (int i = 0; i < 4; i++) {
        if (strcmp(tipo, tiposValidos[i]) == 0) {
            return 1; // Retorna 1 se o tipo da obra for válido
        }
    }
    return 0; // Retorna 0 se o tipo da obra for inválido
}

// Função para validar ano
int validarAno(int ano) {
    return (ano >= 1200 && ano <= 2024); // Verifica se o ano está no intervalo válido
}

// Função para validar preço
int validarPreco(float preco) {
    return (preco > 0); // Verifica se o preço é maior que zero
}

// Função para validar dimensões
int validarDimensoes(int largura, int altura, int profundidade, int peso) {
    return (largura > 0 && altura > 0 && profundidade > 0 && peso > 0); // Verifica se todas as dimensões são maiores que zero
}

// Função para validar localização
int validarLocalizacao(char *localizacao) {
    if (strlen(localizacao) > 50) {
        return 0; // Retorna 0 se a localização tiver mais de 50 caracteres
    }
    for (int i = 0; localizacao[i] != '\0'; i++) {
        if (!isalpha(localizacao[i]) && !isspace(localizacao[i])) {
            return 0; // Retorna 0 se a localização contiver caracteres inválidos
        }
    }
    return 1; // Retorna 1 se a localização for válida
}

// Função para validar estado
int validarEstado(char *estado) {
    const char *estadosValidos[] = {"vendida", "para venda", "apenas exposição", "offsite", "emprestada", "restauro"};
    for (int i = 0; i < 6; i++) {
        if (strcmp(estado, estadosValidos[i]) == 0) {
            return 1; // Retorna 1 se o estado da obra for válido
        }
    }
    return 0; // Retorna 0 se o estado da obra for inválido
}

// Função para validar classificação
int validarClassificacao(int classificacao) {
    return (classificacao >= 0 && classificacao <= 5); // Verifica se a classificação está no intervalo de 0 a 5
}

// Função para guardar as obras de arte em um arquivo
void guardarObrasArquivo(ObraDeArte *lista, const char *arquivo) {
    FILE *fp = fopen(arquivo, "w"); // Abre o arquivo para escrita
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para salvar as obras de arte.\n");
        return;
    }

    while (lista != NULL) {
        fprintf(fp, "Título: %s\n", lista->titulo);
        fprintf(fp, "Artista: %s\n", lista->artista);
        fprintf(fp, "Tipo: %s\n", lista->tipo);
        fprintf(fp, "Ano: %d\n", lista->ano);
        fprintf(fp, "Preço: %.2f\n", lista->preco);
        fprintf(fp, "Dimensões (LxAxPxP): %dx%dx%dx%d\n", lista->dimensao_largura, lista->dimensao_altura, lista->dimensao_profundidade, lista->dimensao_peso);
        fprintf(fp, "Localização: %s\n", lista->localizacao);
        fprintf(fp, "Estado: %s\n", lista->estado);
        fprintf(fp, "Classificação: %d\n", lista->classificacao);
        fprintf(fp, "Notas: %s\n", lista->notas);
        fprintf(fp, "------------------------------\n");
        lista = lista->proximo;
    }

    fclose(fp); // Fecha o arquivo
}

// Função para carregar as obras de arte de um arquivo
ObraDeArte *carregarObrasArquivo(const char *arquivo) {
    ObraDeArte *lista = NULL;
    ObraDeArte *ultimo = NULL;

    FILE *fp = fopen(arquivo, "r"); // Abre o arquivo para leitura
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para carregar as obras de arte.\n");
        return NULL;
    }

    char linha[1024];
    while (fgets(linha, sizeof(linha), fp) != NULL) {
        if (strstr(linha, "Título: ") != NULL) {
            ObraDeArte *novaObra = criarObraDeArte();
            if (novaObra == NULL) {
                printf("Erro ao alocar memória para a obra de arte.\n");
                fclose(fp);
                return NULL;
            }

            sscanf(linha, "Título: %[^\n]", novaObra->titulo);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Artista: %[^\n]", novaObra->artista);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Tipo: %[^\n]", novaObra->tipo);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Ano: %d", &novaObra->ano);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Preço: %f", &novaObra->preco);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Dimensões (LxAxPxP): %d %d %d %d", &novaObra->dimensao_largura, &novaObra->dimensao_altura, &novaObra->dimensao_profundidade, &novaObra->dimensao_peso);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Localização: %[^\n]", novaObra->localizacao);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Estado: %[^\n]", novaObra->estado);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Classificação: %d", &novaObra->classificacao);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Notas: %[^\n]", novaObra->notas);

            if (lista == NULL) {
                lista = novaObra;
                ultimo = lista;
            } else {
                ultimo->proximo = novaObra;
                ultimo = novaObra;
            }
        }
    }

    fclose(fp); // Fecha o arquivo
    return lista; // Retorna a lista carregada
}

// Função para registrar uma nova obra de arte
void registrarObraDeArte(ObraDeArte **lista) {
    ObraDeArte *novaObra = criarObraDeArte();
    if (novaObra == NULL) {
        return;
    }

    printf("Digite o título da obra: ");
    fgets(novaObra->titulo, sizeof(novaObra->titulo), stdin);
    novaObra->titulo[strcspn(novaObra->titulo, "\n")] = '\0';

    while (1) {
        printf("Digite o nome do artista: ");
        fgets(novaObra->artista, sizeof(novaObra->artista), stdin);
        novaObra->artista[strcspn(novaObra->artista, "\n")] = '\0';
        if (validarArtista(novaObra->artista)) {
            break;
        } else {
            printf("Erro: O nome do artista deve conter apenas letras e espaços.\n");
        }
    }

    while (1) {
        printf("Digite o tipo da obra (pintura, escultura, fotografia, outro): ");
        fgets(novaObra->tipo, sizeof(novaObra->tipo), stdin);
        novaObra->tipo[strcspn(novaObra->tipo, "\n")] = '\0';
        if (validarTipoObra(novaObra->tipo)) {
            break;
        } else {
            printf("Erro: Tipo de obra inválido.\n");
        }
    }

    while (1) {
        printf("Digite o ano da obra: ");
        char anoStr[10];
        fgets(anoStr, sizeof(anoStr), stdin);
        int ano;
        if (sscanf(anoStr, "%d", &ano) == 1 && validarAno(ano)) {
            novaObra->ano = ano;
            break;
        } else {
            printf("Erro: Ano inválido.\n");
        }
    }

    while (1) {
        printf("Digite o preço da obra: ");
        char precoStr[10];
        fgets(precoStr, sizeof(precoStr), stdin);
        float preco;
        if (sscanf(precoStr, "%f", &preco) == 1 && validarPreco(preco)) {
            novaObra->preco = preco;
            break;
        } else {
            printf("Erro: Preço inválido.\n");
        }
    }

    while (1) {
        printf("Digite as dimensões da obra (largura altura profundidade peso): ");
        if (scanf("%d %d %d %d", &novaObra->dimensao_largura, &novaObra->dimensao_altura, &novaObra->dimensao_profundidade, &novaObra->dimensao_peso) == 4) {
            if (validarDimensoes(novaObra->dimensao_largura, novaObra->dimensao_altura, novaObra->dimensao_profundidade, novaObra->dimensao_peso)) {
                break;
            } else {
                printf("Erro: Dimensões inválidas.\n");
            }
        } else {
            printf("Erro: Entrada inválida.\n");
            while (getchar() != '\n'); // Limpar o buffer
        }
    }

    getchar(); // Limpar o buffer do teclado

    while (1) {
        printf("Digite a localização da obra: ");
        fgets(novaObra->localizacao, sizeof(novaObra->localizacao), stdin);
        novaObra->localizacao[strcspn(novaObra->localizacao, "\n")] = '\0';
        if (validarLocalizacao(novaObra->localizacao)) {
            break;
        } else {
            printf("Erro: Localização inválida.\n");
        }
    }

    while (1) {
        printf("Digite o estado da obra (vendida, para venda, apenas exposição, offsite, emprestada, restauro): ");
        fgets(novaObra->estado, sizeof(novaObra->estado), stdin);
        novaObra->estado[strcspn(novaObra->estado, "\n")] = '\0';
        if (validarEstado(novaObra->estado)) {
            break;
        } else {
            printf("Erro: Estado inválido.\n");
        }
    }

    while (1) {
        printf("Digite a classificação da obra (0-5): ");
        if (scanf("%d", &novaObra->classificacao) == 1 && validarClassificacao(novaObra->classificacao)) {
            break;
        } else {
            printf("Erro: Classificação inválida.\n");
            while (getchar() != '\n'); // Limpar o buffer
        }
    }

    getchar(); // Limpar o buffer do teclado

    printf("Digite as notas adicionais: ");
    fgets(novaObra->notas, sizeof(novaObra->notas), stdin);
    novaObra->notas[strcspn(novaObra->notas, "\n")] = '\0';

    inserirObraDeArte(lista, novaObra); // Insere a nova obra na lista
    printf("Obra de arte registrada com sucesso.\n");
}

// Função para editar dados de uma obra de arte existente
void editarObraDeArte(ObraDeArte *lista) {
    char titulo[101];
    printf("Digite o título da obra que deseja editar: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    ObraDeArte *obra = procurarObraDeArte(lista, titulo, "titulo"); // Procura a obra pelo título
    if (obra == NULL) {
        printf("Erro: Obra de arte não encontrada.\n");
        return;
    }

    printf("Digite o novo nome do artista (ou pressione Enter para manter o atual): ");
    char artista[51];
    fgets(artista, sizeof(artista), stdin);
    artista[strcspn(artista, "\n")] = '\0';
    if (strlen(artista) > 0) {
        if (validarArtista(artista)) {
            strcpy(obra->artista, artista);
        } else {
            printf("Erro: Nome do artista inválido.\n");
        }
    }

    printf("Digite o novo tipo da obra (ou pressione Enter para manter o atual): ");
    char tipo[20];
    fgets(tipo, sizeof(tipo), stdin);
    tipo[strcspn(tipo, "\n")] = '\0';
    if (strlen(tipo) > 0) {
        if (validarTipoObra(tipo)) {
            strcpy(obra->tipo, tipo);
        } else {
            printf("Erro: Tipo de obra inválido.\n");
        }
    }

    printf("Digite o novo ano da obra (ou pressione Enter para manter o atual): ");
    char anoStr[10];
    fgets(anoStr, sizeof(anoStr), stdin);
    anoStr[strcspn(anoStr, "\n")] = '\0';
    if (strlen(anoStr) > 0) {
        int ano = atoi(anoStr);
        if (validarAno(ano)) {
            obra->ano = ano;
        } else {
            printf("Erro: Ano inválido.\n");
        }
    }

    printf("Digite o novo preço da obra (ou pressione Enter para manter o atual): ");
    char precoStr[10];
    fgets(precoStr, sizeof(precoStr), stdin);
    precoStr[strcspn(precoStr, "\n")] = '\0';
    if (strlen(precoStr) > 0) {
        float preco = atof(precoStr);
        if (validarPreco(preco)) {
            obra->preco = preco;
        } else {
            printf("Erro: Preço inválido.\n");
        }
    }

    printf("Digite as novas dimensões da obra (largura altura profundidade peso) ou pressione Enter para manter as atuais: ");
    char dimensoesStr[50];
    fgets(dimensoesStr, sizeof(dimensoesStr), stdin);
    dimensoesStr[strcspn(dimensoesStr, "\n")] = '\0';
    if (strlen(dimensoesStr) > 0) {
        int largura, altura, profundidade, peso;
        sscanf(dimensoesStr, "%d %d %d %d", &largura, &altura, &profundidade, &peso);
        if (validarDimensoes(largura, altura, profundidade, peso)) {
            obra->dimensao_largura = largura;
            obra->dimensao_altura = altura;
            obra->dimensao_profundidade = profundidade;
            obra->dimensao_peso = peso;
        } else {
            printf("Erro: Dimensões inválidas.\n");
        }
    }

    printf("Digite a nova localização da obra (ou pressione Enter para manter a atual): ");
    char localizacao[51];
    fgets(localizacao, sizeof(localizacao), stdin);
    localizacao[strcspn(localizacao, "\n")] = '\0';
    if (strlen(localizacao) > 0) {
        if (validarLocalizacao(localizacao)) {
            strcpy(obra->localizacao, localizacao);
        } else {
            printf("Erro: Localização inválida.\n");
        }
    }

    printf("Digite o novo estado da obra (ou pressione Enter para manter o atual): ");
    char estado[20];
    fgets(estado, sizeof(estado), stdin);
    estado[strcspn(estado, "\n")] = '\0';
    if (strlen(estado) > 0) {
        if (validarEstado(estado)) {
            strcpy(obra->estado, estado);
        } else {
            printf("Erro: Estado inválido.\n");
        }
    }

    printf("Digite a nova classificação da obra (ou pressione Enter para manter a atual): ");
    char classificacaoStr[10];
    fgets(classificacaoStr, sizeof(classificacaoStr), stdin);
    classificacaoStr[strcspn(classificacaoStr, "\n")] = '\0';
    if (strlen(classificacaoStr) > 0) {
        int classificacao = atoi(classificacaoStr);
        if (validarClassificacao(classificacao)) {
            obra->classificacao = classificacao;
        } else {
            printf("Erro: Classificação inválida.\n");
        }
    }

    printf("Digite as novas notas adicionais (ou pressione Enter para manter as atuais): ");
    char notas[301];
    fgets(notas, sizeof(notas), stdin);
    notas[strcspn(notas, "\n")] = '\0';
    if (strlen(notas) > 0) {
        strcpy(obra->notas, notas);
    }

    printf("Obra de arte atualizada com sucesso.\n");
}

// Função para listar todas as obras de arte
void listarObrasDeArte(ObraDeArte *lista) {
    if (lista == NULL) {
        printf("Nenhuma obra de arte registrada.\n");
        return;
    }

    while (lista != NULL) {
        printf("Título: %s\n", lista->titulo);
        printf("Artista: %s\n", lista->artista);
        printf("Tipo: %s\n", lista->tipo);
        printf("Ano: %d\n", lista->ano);
        printf("Preço: %.2f\n", lista->preco);
        printf("Dimensões (LxAxPxP): %dx%dx%dx%d\n", lista->dimensao_largura, lista->dimensao_altura, lista->dimensao_profundidade, lista->dimensao_peso);
        printf("Localização: %s\n", lista->localizacao);
        printf("Estado: %s\n", lista->estado);
        printf("Classificação: %d\n", lista->classificacao);
        printf("Notas: %s\n", lista->notas);
        printf("------------------------------\n");
        lista = lista->proximo;
    }
}

// Função para pesquisar obras de arte por artista
void pesquisarObrasDeArte(ObraDeArte *lista, char *artista) {
    int encontrou = 0;
    while (lista != NULL) {
        if (strcmp(lista->artista, artista) == 0) {
            printf("Título: %s\n", lista->titulo);
            printf("Artista: %s\n", lista->artista);
            printf("Tipo: %s\n", lista->tipo);
            printf("Ano: %d\n", lista->ano);
            printf("Preço: %.2f\n", lista->preco);
            printf("Dimensões (LxAxPxP): %dx%dx%dx%d\n", lista->dimensao_largura, lista->dimensao_altura, lista->dimensao_profundidade, lista->dimensao_peso);
            printf("Localização: %s\n", lista->localizacao);
            printf("Estado: %s\n", lista->estado);
            printf("Classificação: %d\n", lista->classificacao);
            printf("Notas: %s\n", lista->notas);
            printf("------------------------------\n");
            encontrou = 1;
        }
        lista = lista->proximo;
    }
    if (!encontrou) {
        printf("Nenhuma obra de arte encontrada para o artista %s.\n", artista);
    }
}

// Função de menu
void menu(ObraDeArte **lista) {
    int opcao;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Registrar nova obra de arte\n");
        printf("2. Editar obra de arte\n");
        printf("3. Listar todas as obras de arte\n");
        printf("4. Pesquisar obras de arte por artista\n");
        printf("5. Guardar obras de arte\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
            case 1:
                registrarObraDeArte(lista); // Chama a função para registrar uma nova obra de arte
                break;
            case 2:
                editarObraDeArte(*lista); // Chama a função para editar uma obra de arte existente
                break;
            case 3:
                listarObrasDeArte(*lista); // Chama a função para listar todas as obras de arte
                break;
            case 4: {
                char artista[51];
                printf("Digite o nome do artista: ");
                fgets(artista, sizeof(artista), stdin);
                artista[strcspn(artista, "\n")] = '\0';
                pesquisarObrasDeArte(*lista, artista); // Chama a função para pesquisar obras de arte por artista
                break;
            }
            case 5:
                guardarObrasArquivo(*lista, "obras_de_arte.txt"); // Chama a função para guardar as obras de arte em um arquivo
                break;
            case 0:
                printf("A Sair...\n");
                break;
            default:
                printf("Opção inválida. Tenta novamente.\n");
                break;
        }
    } while (opcao != 0);

    while (*lista != NULL) {
        ObraDeArte *obra = *lista;
        *lista = (*lista)->proximo;
        liberarObraDeArte(obra); // Libera a memória de cada obra de arte ao sair
    }
}

int main() {
    ObraDeArte *lista = carregarObrasArquivo("obras_de_arte.txt"); // Carrega as obras de arte do arquivo
    menu(&lista); // Chama o menu para interagir com o utilizador
    return 0;
}
