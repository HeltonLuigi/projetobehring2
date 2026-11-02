#include <stdio.h>
#include <string.h>
int op = 0;
FILE *p;
char item[51];
int q;
int exe(void);
int end(void);
int main(void);
int add(){
    p = fopen("inventory.txt", "a");
    if(p == NULL){
        printf("erro");
    }else{
    printf("Digite o nome do item:");
    scanf("%50s", item);
    printf("Digite a quantidade: ");
    scanf("%d", &q);
    fprintf(p, "%s\n%d\n", item, q);
    printf("Item adicionado com sucesso!");
    }
}
int list(){
    p = fopen("inventory.txt", "r");
    if(p == NULL){
    printf("O estoque está vazio.");
    }else{
        
        int x = 0;
        
        while(fscanf(p, "%s %d", item, &q) == 2){
        x++;
            if(x ==1 ){
            printf("===============================\n");
            printf("        Estoque Atual\n");
            printf("===============================\n");
            printf("Nome:%s\nQuantidade:%d\n\n", item, q);
            }else{
            printf("Nome:%s\nQuantidade:%d\n\n", item, q);
            }
            
        
        }
        if(x==0){
            printf("O estoque está vazio.\n");
        }
        fclose(p);
    }
}
int criar(){
    p = fopen("inventory.txt", "a");
    if(p == NULL){
    printf("erro");
    }else{
        fclose(p);
    }
}

int main(void) {
    char linha[100];
    char extra;
    int leitura;
    criar();
    printf("===============================\n");
    printf("   Controle de Estoque\n");
    printf("===============================\n");
    printf("Selecione uma operação:\n");
    printf("1. Adicionar Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Estoque\n");
    printf("4. Sair\n");

    do {
        printf("Opção: ");

        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            return 0;
        }

        leitura = sscanf(linha, " %d %c", &op, &extra);

        if (leitura != 1 || op < 1 || op > 4) {
            printf("Opção inválida! Tente novamente.\n");
        }

    } while (leitura != 1 || op < 1 || op > 4);
    exe();
    return 0;
}
int exe(void){
    
    
    if (op == 1){
        add();
        end();
    }
    else if(op == 2){
        end();
    }
    else if(op == 3){
        list();
        end();
    }
    else if(op == 4){
        printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
    }

}
int end(void){
    char x;
    printf("Deseja realizar outra operação? (s/n)\n");
    scanf(" %c", &x);
    if (x == 'S' || x == 's') {
        main();
    } else{
        printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
    }
}


