#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Defini��o da struct para armazenar dados da obra de arte
typedef struct ObraDeArte {
    char titulo[101]; // T�tulo da obra de arte
    char artista[51]; // Nome do artista respons�vel pela obra
    char tipo[20]; // Tipo da obra (pintura, escultura, fotografia, etc.)
    int ano; // Ano de cria��o da obra
    float preco; // Pre�o da obra
    int dimensao_largura; // Largura da obra
    int dimensao_altura; // Altura da obra
    int dimensao_profundidade; // Profundidade da obra
    int dimensao_peso; // Peso da obra
    char localizacao[51]; // Localiza��o atual da obra
    char estado[20]; // Estado atual da obra (vendida, para venda, etc.)
    int classificacao; // Classifica��o da obra (de 0 a 5)
    char notas[301]; // Notas adicionais sobre a obra
    struct ObraDeArte *proximo; // Ponteiro para o pr�ximo elemento da lista encadeada
} ObraDeArte;

// Declara��es das fun��es de valida��o
int validarArtista(char *artista); // Fun��o para validar o nome do artista
int validarTipoObra(char *tipo); // Fun��o para validar o tipo da obra
int validarAno(int ano); // Fun��o para validar o ano da obra
int validarPreco(float preco); // Fun��o para validar o pre�o da obra
int validarDimensoes(int largura, int altura, int profundidade, int peso); // Fun��o para validar as dimens�es da obra
int validarLocalizacao(char *localizacao); // Fun��o para validar a localiza��o da obra
int validarEstado(char *estado); // Fun��o para validar o estado da obra
int validarClassificacao(int classificacao); // Fun��o para validar a classifica��o da obra

// Fun��o para criar uma nova obra de arte (aloca mem�ria)
ObraDeArte *criarObraDeArte() {
    ObraDeArte *novaObra = (ObraDeArte *)malloc(sizeof(ObraDeArte)); // Aloca mem�ria para uma nova obra
    if (novaObra == NULL) { // Verifica se a aloca��o foi bem-sucedida
        printf("Erro ao alocar mem�ria para a obra de arte.\n");
        return NULL;
    }
    novaObra->proximo = NULL; // Inicializa o ponteiro para o pr�ximo elemento como NULL
    return novaObra; // Retorna o ponteiro para a nova obra
}

// Fun��o para liberar a mem�ria de uma obra de arte
void liberarObraDeArte(ObraDeArte *obra) {
    if (obra != NULL) {
        free(obra); // Libera a mem�ria alocada para a obra de arte
    }
}

// Fun��o para inserir uma obra de arte na lista encadeada
void inserirObraDeArte(ObraDeArte **lista, ObraDeArte *novaObra) {
    if (novaObra == NULL) {
        return;
    }

    novaObra->proximo = *lista; // Define o pr�ximo da nova obra como o primeiro elemento da lista
    *lista = novaObra; // Atualiza a cabe�a da lista para a nova obra
}

// Fun��o para buscar uma obra de arte na lista encadeada
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
    return NULL; // Retorna NULL se a obra n�o for encontrada
}

// Fun��o para validar artista
int validarArtista(char *artista) {
    for (int i = 0; artista[i] != '\0'; i++) {
        if (!isalpha(artista[i]) && !isspace(artista[i])) {
            return 0; // Retorna 0 se o nome do artista contiver caracteres inv�lidos
        }
    }
    return 1; // Retorna 1 se o nome do artista for v�lido
}

// Fun��o para validar tipo de obra
int validarTipoObra(char *tipo) {
    const char *tiposValidos[] = {"pintura", "escultura", "fotografia", "outro"}; // Tipos v�lidos de obras
    for (int i = 0; i < 4; i++) {
        if (strcmp(tipo, tiposValidos[i]) == 0) {
            return 1; // Retorna 1 se o tipo da obra for v�lido
        }
    }
    return 0; // Retorna 0 se o tipo da obra for inv�lido
}

// Fun��o para validar ano
int validarAno(int ano) {
    return (ano >= 1200 && ano <= 2024); // Verifica se o ano est� no intervalo v�lido
}

// Fun��o para validar pre�o
int validarPreco(float preco) {
    return (preco > 0); // Verifica se o pre�o � maior que zero
}

// Fun��o para validar dimens�es
int validarDimensoes(int largura, int altura, int profundidade, int peso) {
    return (largura > 0 && altura > 0 && profundidade > 0 && peso > 0); // Verifica se todas as dimens�es s�o maiores que zero
}

// Fun��o para validar localiza��o
int validarLocalizacao(char *localizacao) {
    if (strlen(localizacao) > 50) {
        return 0; // Retorna 0 se a localiza��o tiver mais de 50 caracteres
    }
    for (int i = 0; localizacao[i] != '\0'; i++) {
        if (!isalpha(localizacao[i]) && !isspace(localizacao[i])) {
            return 0; // Retorna 0 se a localiza��o contiver caracteres inv�lidos
        }
    }
    return 1; // Retorna 1 se a localiza��o for v�lida
}

// Fun��o para validar estado
int validarEstado(char *estado) {
    const char *estadosValidos[] = {"vendida", "para venda", "apenas exposi��o", "offsite", "emprestada", "restauro"};
    for (int i = 0; i < 6; i++) {
        if (strcmp(estado, estadosValidos[i]) == 0) {
            return 1; // Retorna 1 se o estado da obra for v�lido
        }
    }
    return 0; // Retorna 0 se o estado da obra for inv�lido
}

// Fun��o para validar classifica��o
int validarClassificacao(int classificacao) {
    return (classificacao >= 0 && classificacao <= 5); // Verifica se a classifica��o est� no intervalo de 0 a 5
}

// Fun��o para guardar as obras de arte em um arquivo
void guardarObrasArquivo(ObraDeArte *lista, const char *arquivo) {
    FILE *fp = fopen(arquivo, "w"); // Abre o arquivo para escrita
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para salvar as obras de arte.\n");
        return;
    }

    while (lista != NULL) {
        fprintf(fp, "T�tulo: %s\n", lista->titulo);
        fprintf(fp, "Artista: %s\n", lista->artista);
        fprintf(fp, "Tipo: %s\n", lista->tipo);
        fprintf(fp, "Ano: %d\n", lista->ano);
        fprintf(fp, "Pre�o: %.2f\n", lista->preco);
        fprintf(fp, "Dimens�es (LxAxPxP): %dx%dx%dx%d\n", lista->dimensao_largura, lista->dimensao_altura, lista->dimensao_profundidade, lista->dimensao_peso);
        fprintf(fp, "Localiza��o: %s\n", lista->localizacao);
        fprintf(fp, "Estado: %s\n", lista->estado);
        fprintf(fp, "Classifica��o: %d\n", lista->classificacao);
        fprintf(fp, "Notas: %s\n", lista->notas);
        fprintf(fp, "------------------------------\n");
        lista = lista->proximo;
    }

    fclose(fp); // Fecha o arquivo
}

// Fun��o para carregar as obras de arte de um arquivo
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
        if (strstr(linha, "T�tulo: ") != NULL) {
            ObraDeArte *novaObra = criarObraDeArte();
            if (novaObra == NULL) {
                printf("Erro ao alocar mem�ria para a obra de arte.\n");
                fclose(fp);
                return NULL;
            }

            sscanf(linha, "T�tulo: %[^\n]", novaObra->titulo);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Artista: %[^\n]", novaObra->artista);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Tipo: %[^\n]", novaObra->tipo);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Ano: %d", &novaObra->ano);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Pre�o: %f", &novaObra->preco);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Dimens�es (LxAxPxP): %d %d %d %d", &novaObra->dimensao_largura, &novaObra->dimensao_altura, &novaObra->dimensao_profundidade, &novaObra->dimensao_peso);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Localiza��o: %[^\n]", novaObra->localizacao);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Estado: %[^\n]", novaObra->estado);
            fgets(linha, sizeof(linha), fp);
            sscanf(linha, "Classifica��o: %d", &novaObra->classificacao);
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

// Fun��o para registrar uma nova obra de arte
void registrarObraDeArte(ObraDeArte **lista) {
    ObraDeArte *novaObra = criarObraDeArte();
    if (novaObra == NULL) {
        return;
    }

    printf("Digite o t�tulo da obra: ");
    fgets(novaObra->titulo, sizeof(novaObra->titulo), stdin);
    novaObra->titulo[strcspn(novaObra->titulo, "\n")] = '\0';

    while (1) {
        printf("Digite o nome do artista: ");
        fgets(novaObra->artista, sizeof(novaObra->artista), stdin);
        novaObra->artista[strcspn(novaObra->artista, "\n")] = '\0';
        if (validarArtista(novaObra->artista)) {
            break;
        } else {
            printf("Erro: O nome do artista deve conter apenas letras e espa�os.\n");
        }
    }

    while (1) {
        printf("Digite o tipo da obra (pintura, escultura, fotografia, outro): ");
        fgets(novaObra->tipo, sizeof(novaObra->tipo), stdin);
        novaObra->tipo[strcspn(novaObra->tipo, "\n")] = '\0';
        if (validarTipoObra(novaObra->tipo)) {
            break;
        } else {
            printf("Erro: Tipo de obra inv�lido.\n");
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
            printf("Erro: Ano inv�lido.\n");
        }
    }

    while (1) {
        printf("Digite o pre�o da obra: ");
        char precoStr[10];
        fgets(precoStr, sizeof(precoStr), stdin);
        float preco;
        if (sscanf(precoStr, "%f", &preco) == 1 && validarPreco(preco)) {
            novaObra->preco = preco;
            break;
        } else {
            printf("Erro: Pre�o inv�lido.\n");
        }
    }

    while (1) {
        printf("Digite as dimens�es da obra (largura altura profundidade peso): ");
        if (scanf("%d %d %d %d", &novaObra->dimensao_largura, &novaObra->dimensao_altura, &novaObra->dimensao_profundidade, &novaObra->dimensao_peso) == 4) {
            if (validarDimensoes(novaObra->dimensao_largura, novaObra->dimensao_altura, novaObra->dimensao_profundidade, novaObra->dimensao_peso)) {
                break;
            } else {
                printf("Erro: Dimens�es inv�lidas.\n");
            }
        } else {
            printf("Erro: Entrada inv�lida.\n");
            while (getchar() != '\n'); // Limpar o buffer
        }
    }

    getchar(); // Limpar o buffer do teclado

    while (1) {
        printf("Digite a localiza��o da obra: ");
        fgets(novaObra->localizacao, sizeof(novaObra->localizacao), stdin);
        novaObra->localizacao[strcspn(novaObra->localizacao, "\n")] = '\0';
        if (validarLocalizacao(novaObra->localizacao)) {
            break;
        } else {
            printf("Erro: Localiza��o inv�lida.\n");
        }
    }

    while (1) {
        printf("Digite o estado da obra (vendida, para venda, apenas exposi��o, offsite, emprestada, restauro): ");
        fgets(novaObra->estado, sizeof(novaObra->estado), stdin);
        novaObra->estado[strcspn(novaObra->estado, "\n")] = '\0';
        if (validarEstado(novaObra->estado)) {
            break;
        } else {
            printf("Erro: Estado inv�lido.\n");
        }
    }

    while (1) {
        printf("Digite a classifica��o da obra (0-5): ");
        if (scanf("%d", &novaObra->classificacao) == 1 && validarClassificacao(novaObra->classificacao)) {
            break;
        } else {
            printf("Erro: Classifica��o inv�lida.\n");
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

// Fun��o para editar dados de uma obra de arte existente
void editarObraDeArte(ObraDeArte *lista) {
    char titulo[101];
    printf("Digite o t�tulo da obra que deseja editar: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    ObraDeArte *obra = procurarObraDeArte(lista, titulo, "titulo"); // Procura a obra pelo t�tulo
    if (obra == NULL) {
        printf("Erro: Obra de arte n�o encontrada.\n");
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
            printf("Erro: Nome do artista inv�lido.\n");
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
            printf("Erro: Tipo de obra inv�lido.\n");
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
            printf("Erro: Ano inv�lido.\n");
        }
    }

    printf("Digite o novo pre�o da obra (ou pressione Enter para manter o atual): ");
    char precoStr[10];
    fgets(precoStr, sizeof(precoStr), stdin);
    precoStr[strcspn(precoStr, "\n")] = '\0';
    if (strlen(precoStr) > 0) {
        float preco = atof(precoStr);
        if (validarPreco(preco)) {
            obra->preco = preco;
        } else {
            printf("Erro: Pre�o inv�lido.\n");
        }
    }

    printf("Digite as novas dimens�es da obra (largura altura profundidade peso) ou pressione Enter para manter as atuais: ");
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
            printf("Erro: Dimens�es inv�lidas.\n");
        }
    }

    printf("Digite a nova localiza��o da obra (ou pressione Enter para manter a atual): ");
    char localizacao[51];
    fgets(localizacao, sizeof(localizacao), stdin);
    localizacao[strcspn(localizacao, "\n")] = '\0';
    if (strlen(localizacao) > 0) {
        if (validarLocalizacao(localizacao)) {
            strcpy(obra->localizacao, localizacao);
        } else {
            printf("Erro: Localiza��o inv�lida.\n");
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
            printf("Erro: Estado inv�lido.\n");
        }
    }

    printf("Digite a nova classifica��o da obra (ou pressione Enter para manter a atual): ");
    char classificacaoStr[10];
    fgets(classificacaoStr, sizeof(classificacaoStr), stdin);
    classificacaoStr[strcspn(classificacaoStr, "\n")] = '\0';
    if (strlen(classificacaoStr) > 0) {
        int classificacao = atoi(classificacaoStr);
        if (validarClassificacao(classificacao)) {
            obra->classificacao = classificacao;
        } else {
            printf("Erro: Classifica��o inv�lida.\n");
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

// Fun��o para listar todas as obras de arte
void listarObrasDeArte(ObraDeArte *lista) {
    if (lista == NULL) {
        printf("Nenhuma obra de arte registrada.\n");
        return;
    }

    while (lista != NULL) {
        printf("T�tulo: %s\n", lista->titulo);
        printf("Artista: %s\n", lista->artista);
        printf("Tipo: %s\n", lista->tipo);
        printf("Ano: %d\n", lista->ano);
        printf("Pre�o: %.2f\n", lista->preco);
        printf("Dimens�es (LxAxPxP): %dx%dx%dx%d\n", lista->dimensao_largura, lista->dimensao_altura, lista->dimensao_profundidade, lista->dimensao_peso);
        printf("Localiza��o: %s\n", lista->localizacao);
        printf("Estado: %s\n", lista->estado);
        printf("Classifica��o: %d\n", lista->classificacao);
        printf("Notas: %s\n", lista->notas);
        printf("------------------------------\n");
        lista = lista->proximo;
    }
}

// Fun��o para pesquisar obras de arte por artista
void pesquisarObrasDeArte(ObraDeArte *lista, char *artista) {
    int encontrou = 0;
    while (lista != NULL) {
        if (strcmp(lista->artista, artista) == 0) {
            printf("T�tulo: %s\n", lista->titulo);
            printf("Artista: %s\n", lista->artista);
            printf("Tipo: %s\n", lista->tipo);
            printf("Ano: %d\n", lista->ano);
            printf("Pre�o: %.2f\n", lista->preco);
            printf("Dimens�es (LxAxPxP): %dx%dx%dx%d\n", lista->dimensao_largura, lista->dimensao_altura, lista->dimensao_profundidade, lista->dimensao_peso);
            printf("Localiza��o: %s\n", lista->localizacao);
            printf("Estado: %s\n", lista->estado);
            printf("Classifica��o: %d\n", lista->classificacao);
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

// Fun��o de menu
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
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
            case 1:
                registrarObraDeArte(lista); // Chama a fun��o para registrar uma nova obra de arte
                break;
            case 2:
                editarObraDeArte(*lista); // Chama a fun��o para editar uma obra de arte existente
                break;
            case 3:
                listarObrasDeArte(*lista); // Chama a fun��o para listar todas as obras de arte
                break;
            case 4: {
                char artista[51];
                printf("Digite o nome do artista: ");
                fgets(artista, sizeof(artista), stdin);
                artista[strcspn(artista, "\n")] = '\0';
                pesquisarObrasDeArte(*lista, artista); // Chama a fun��o para pesquisar obras de arte por artista
                break;
            }
            case 5:
                guardarObrasArquivo(*lista, "obras_de_arte.txt"); // Chama a fun��o para guardar as obras de arte em um arquivo
                break;
            case 0:
                printf("A Sair...\n");
                break;
            default:
                printf("Op��o inv�lida. Tenta novamente.\n");
                break;
        }
    } while (opcao != 0);

    while (*lista != NULL) {
        ObraDeArte *obra = *lista;
        *lista = (*lista)->proximo;
        liberarObraDeArte(obra); // Libera a mem�ria de cada obra de arte ao sair
    }
}

int main() {
    ObraDeArte *lista = carregarObrasArquivo("obras_de_arte.txt"); // Carrega as obras de arte do arquivo
    menu(&lista); // Chama o menu para interagir com o utilizador
    return 0;
}
