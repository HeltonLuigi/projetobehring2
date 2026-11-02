
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

int add(void){
    p = fopen("inventory.txt", "a");
    if(p == NULL){
        printf("Erro ao abrir estoque.\n");
        return 0;
    }else{
        printf("Digite o nome do item: ");
        if(scanf("%50s", item) != 1){
            fclose(p);
            return 0;
        }
        printf("Digite a quantidade: ");
        if(scanf("%d", &q) != 1 || q <= 0){
            printf("Quantidade inválida.\n");
            fclose(p);
            return 0;
        }
        if(fprintf(p, "%s\n%d\n", item, q) < 0){
            printf("Erro ao salvar item.\n");
            fclose(p);
            return 0;
        }
        if(fclose(p) != 0){
            printf("Erro ao salvar item.\n");
            return 0;
        }
        printf("Item adicionado com sucesso!\n");
    }
    return 1;
}

int list(void){
    p = fopen("inventory.txt", "r");
    if(p == NULL){
        printf("O estoque está vazio.\n");
        return 0;
    }else{
        int x = 0;
        while(fscanf(p, "%50s %d", item, &q) == 2){
            x++;
            if(x == 1){
                printf("=============================\n");
                printf("        Estoque Atual\n");
                printf("=============================\n");
            }
            printf("Nome: %s\nQuantidade: %d\n\n", item, q);
        }
        if(x == 0){
            printf("O estoque está vazio.\n");
        }
        fclose(p);
    }
    return 1;
}

int remover(void){
    char i[51];
    int r;
    int f = 0;
    int a = 0;
    int excluiu = 0;

    p = fopen("inventory.txt", "r");

    if(p == NULL){
        printf("Item não encontrado.\n");
        return 0;
    }else{
        printf("Digite o nome do item: ");
        if(scanf("%50s", i) != 1){
            fclose(p);
            return 0;
        }
        printf("Digite a quantidade a ser removida: ");
        if(scanf("%d", &r) != 1 || r <= 0){
            printf("Quantidade inválida.\n");
            fclose(p);
            return 0;
        }

        while(fscanf(p, "%50s %d", item, &q) == 2){
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
            while(fscanf(p, "%50s %d", item, &q) == 2){
                if(strcmp(i, item) == 0 && a == 0){
                    a = 1;
                    if(q > r){
                        q = q - r;
                        fprintf(t, "%s\n%d\n", item, q);
                    }else if(q == r){
                        excluiu = 1;
                    }
                }else{
                    fprintf(t, "%s\n%d\n", item, q);
                }
            }
        }

        fclose(p);

        if(fclose(t) != 0){
            printf("Erro ao salvar arquivo temporário.\n");
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

        if(excluiu == 1){
            printf("Item removido do estoque!\n");
        }else{
            printf("Quantidade atualizada com sucesso!\n");
        }
    }
    return 1;
}

int criar(void){
    p = fopen("inventory.txt", "a");
    if(p == NULL){
        printf("Erro ao abrir estoque.\n");
        return 0;
    }else{
        if(fclose(p) != 0){
            printf("Erro ao fechar estoque.\n");
            return 0;
        }
    }
    return 1;
}

int main(void){
    char linha[100];
    char extra;
    int leitura;
    int continuar = 1;

    if(criar() == 0){
        return 1;
    }

    do{
        printf("================================\n");
        printf("   Controle de Estoque\n");
        printf("================================\n");
        printf("Selecione uma opção:\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Estoque\n");
        printf("4. Sair\n");

        do{
            printf("Opção: ");
            if(fgets(linha, sizeof(linha), stdin) == NULL){
                return 0;
            }

            leitura = sscanf(linha, " %d %c", &op, &extra);

            if(leitura != 1 || op < 1 || op > 4){
                printf("Opção inválida! Tente novamente.\n");
            }
        }while(leitura != 1 || op < 1 || op > 4);

        continuar = exe();
    }while(continuar == 1);

    return 0;
}

int exe(void){
    if(op == 1){
        add();
        return end();
    }
    else if(op == 2){
        remover();
        return end();
    }
    else if(op == 3){
        list();
        return end();
    }
    else if(op == 4){
        printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
        return 0;
    }
    return 0;
}

int end(void){
    char x;
    int c;

    printf("Deseja realizar outra operação? (s/n): ");

    if(scanf(" %c", &x) != 1){
        printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
        return 0;
    }

    while((c = getchar()) != '\n' && c != EOF){
    }

    if(x == 'S' || x == 's'){
        return 1;
    }else{
        printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
        return 0;
    }
}
