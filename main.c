#include <stdio.h>
#include <string.h>
int op = 0;
FILE *p;
FILE *t;
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
int remover(void){
    char i[51];
    int r;
    int f = 0;
    int a = 0;

    p = fopen("inventory.txt", "r");

    if(p == NULL){
        printf("Item não encontrado.\n");
        return 0;
    }else{
        printf("Digite o nome do item: ");
        scanf("%50s", i);

        printf("Digite a quantidade a ser removida: ");
        if(scanf("%d", &r) != 1 || r <= 0){
            printf("Quantidade inválida.\n");
            fclose(p);
            return 0;
        }
        while(fscanf(p, "%49s %d", item, &q) == 2){
            if(strcmp(i, item) == 0){
                f = 1;

                if(q < r){
                    printf("Estoque insuficiente. Quantidade disponível: %d\n", q);
                    fclose(p);
                    return 0;
                }

                break;
            }
        }
        if(f == 0){
            printf("Item não encontrado.\n");
            fclose(p);
            return 0;
        }
        rewind(p);
        t = fopen("temp.txt", "w");
        if(t == NULL){
            printf("Erro ao criar arquivo temporário.\n");
            fclose(p);
            return 0;
        }else{

            while(fscanf(p, "%49s %d", item, &q) == 2){

                if(strcmp(i, item) == 0 && a == 0){
                    a = 1;

                    if(q > r){
                        q = q - r;
                        fprintf(t, "%s\n%d\n", item, q);
                    }
                    else if(q == r){
                        // Não grava o produto
                    }
                }else{
                    fprintf(t, "%s\n%d\n", item, q);
                }
            }
        }

        fclose(p);

        if(fclose(t) != 0){
            printf("Erro ao salvar o arquivo temporário.\n");
            remove("temp.txt");
            return 0;
        }
        if(rename("inventory.txt", "inventory_backup.txt") != 0){
            printf("Erro ao preparar a atualização.\n");
            remove("temp.txt");
            return 0;
        }

        if(rename("temp.txt", "inventory.txt") != 0){
            printf("Erro ao atualizar estoque.\n");

            if(rename("inventory_backup.txt", "inventory.txt") != 0){
                printf("Verifique o arquivo inventory_backup.txt.\n");
            }

            return 0;
        }
        remove("inventory_backup.txt");

        if(q >= 0){
        }
        p = fopen("inventory.txt", "r");
        f = 0;

        if(p != NULL){
            while(fscanf(p, "%49s %d", item, &q) == 2){
                if(strcmp(i, item) == 0){
                    f = 1;
                    break;
                }
            }
            fclose(p);
        }

        if(f == 0){
            printf("Item removido do estoque!\n");
        }else{
            printf("Quantidade atualizada com sucesso!\n");
        }
    }
    return 1;
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
        remover();
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


