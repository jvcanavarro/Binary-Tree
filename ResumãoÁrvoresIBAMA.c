#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

// ----Resumo Árvores----

//'*'->Não visto em sala, ou abordado de forma diferente.

//Obs: Diferente das aulas do professor Cleidson, a criação da árvore é feita quando alocamos espaço para a raiz ( a raiz não recebe valores ), que aponta para o nó central, o qual irá receber o primeiro valor. Nas aulas do professor, não tinhamos a raiz, o que exigiria algumas pequenas alterações nas funções.

// FONTE : https://www.youtube.com/playlist?list=PL8iN9FQ7_jt6H5m4Gm0H89sybzR9yaaka (Playlist em Português, contém todos os assuntos de TAD)

// 1) Implementação*

struct NO{
    int info;
    struct NO* esq;
    struct NO* dir;
};

typedef struct NO* ArvBin;

// 2) Criar Árvore Binária

ArvBin* cria_ArvBin(){
    ArvBin *raiz = (ArvBin*) malloc (sizeof(ArvBin));
    if (raiz != NULL) *raiz = NULL;     // Checa se Árvore foi corretamente alocada.
    return raiz;
}

// 3) Destruir Árvore Binária*

void libera_NO(struct NO* no){
    if (no == NULL) return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(Arvbin* raiz){
    if (raiz == NULL) return;
    libera_NO(*raiz);   // Libera cada nó da árvore.
    free(raiz);         // Libera raiz.
}

// 4) Testar Árvore Vazia*

int estaVazia_ArvBin(ArvBin *raiz){
    if (raiz == NULL) return 1; //Raiz null = Erro na criação da arvoré
    if (*raiz == NULL) return 1; // Conteúdo da raiz null =  Nenhum nó inserido ainda.
    /* else */
    return 0;
}

// 5) Altura da Árvore*

int altura_ArvBin(ArvBin *raiz){        // Argumento = Endereço de Nó
    if (raiz == NULL) return 0;
    if (*raiz == NULL) return 0;
    int alt_esq = altura_ArvBin(raiz)->esq);
    int alt_esd = altura_ArvBin(raiz->dir);
    if (alt_esq > alt_dir) return (alt_esq + 1); //"Subindo" na arvoré acrescenta em 1 na altura.
    else return (alt_dir + 1);
}

// 6) Número de Nós na Árvore*

int totalNO_ArvBin(ArvBin *raiz){       // Função similar à de encontrar Altura.
    if (raiz == NULL) return 0;
    if (*raiz == NULL) return 0;
    int alt_esq = totalNO_ArvBin(raiz->esq);
    int alt_dir = totalNO_ArvBin(raiz->dir);
    return (alt_esq + alt_dir + 1);
}

// 7) Percorrendo Árvore Binaria : Pré_Ordem, Pós_Ordem, Ordem_Central

// 8) Inserção Em Árvore Bin. de Busca (onde todos os elementos menores ao nó central estão à esquerda e os maiores à direita).

int insere_ArvBin(ArvBin* raiz, int valor){
    if (raiz == NULL) return 0; // Erro na raiz
    strucdt NO* novo;
    novo = (struct NO*) malloc (sizeof(struct NO));
    if (novo == NULL) return 0;     // Não conseguiu alocar espaço para 'novo'
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;
    // Agora, procura o local correto na árvore para inserir o nó que acabou de ser criado.
    if (*raiz == NULL) *raiz = novo; // Primeiro Caso > Árvore Vazia.
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while (atual != NULL){  // Navega nos nós até chegar ao nó correto.
            ant = atual;
            if(valor == atual->info){
                free(novo);
                return 0;       // Elemento já existe.
            }
            if (valor > atual->info) atual = atual->dir;
            else atual = atual->esq;
        }
        // Insere novo nó à esquerda ou direita segundo resultados da comparação.
        if (valor > ant->info) ant->dir = novo;
        else ant->esq = novo;
    }
    return 1;
}

// 9) Remoção de Árvore Bin. de Busca. Cuidado: Não se pode remover de árvore vazia. (Mais complicado que a função do slide da aula)

int remove_ArvBin(ArvBin *raiz, int valor){
    if (raiz == NULL) return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    //Procurar o nó a ser removido.
    while (atual != NULL){
        if (valor == atual->info){
            if (atual == *raiz) *raiz = remove_atual();
            else{
                if (ant->dir == atual) ant->dir = remove_atual(atual);
                else ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(valor < atual->info) atual = atual->dir;
        else atual = atual esq;
    }
}

struct NO* remove_atual(struct NO* atual){
    struct NO *no1, *no2;
    if (atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while (no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }

    if (no1 != atual){
        no1->dir = no2->esq;
        no2->esq atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

// 10) Consulta em Árvore Bin. de Busca. Parecido com "dividir para conquistar".

int consulta_ArvBin(ArvBin *raiz, int valor){
    if (raiz == NULL) return 0;
    struct NO* atual = *raiz;
    while (atual != NULL){
        if (valor == atual->info) return 1;
        if (valor > atual->info) atual = atual->dir;
        else atual = atual->esq;
    }
    return 0;
}
int main (){
    setlocale(LC_ALL , "Portuguese");  //Aceita 'ç' e acentos.
    ArvBin *raiz; // Raiz da árvore, aponta para nulo até o primeiro nó ser criado e inserido, ponteiro para ponteiro.
    ArvBin *raiz = cria_ArvBin(); // Substitui a linha de cima, não possui informações apenas aponta para o primeiro nó.

    libera_ArvBin(raiz);

    //if(estaVazia_ArvBin(raiz))

    int x = altura_ArvBin(raiz);

    int y = totalNO_ArvBin(raiz);

    int z = insere_ArvBin(raiz, valor);

    int w = remove_ArvBin(raiz, valor);
    return 0;
}
