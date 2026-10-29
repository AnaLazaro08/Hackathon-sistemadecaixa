/*
Equipe:
Matricula: 202602658224 - Ana Gabryelli Jesus Lazaro
Matricula: 202601423151 - Leiryel Wylliam Smaniotto Ribeiro
Matricula: 202603080269 - João Pedro Moreira Mazzeo
Matricula: 202601733851 - Gabriel Noveli 

Disciplina: WYD6376 - Introducao a Programacao de Computadores
Professor: Kesede Rodrigues Julio
Projeto: Hackathon em C - Sistema de Caixa de Supermercado
*/

#include <stdio.h>

struct Produto {
    int codigo;
    char nome[30];
    float preco;
    int estoque;
};

struct ItemCompra {
    int codigo;
    char nome[30];
    float preco;
    int quantidade;
    float subtotal;
};

struct Produto produtos[100];
struct ItemCompra carrinho[50];
struct ItemCompra ultimoCupom[50];

int totalProdutos = 0;
int totalItens = 0;
int totalItensUltimoCupom = 0;

int caixaAberto = 0;
int quantidadeVendas = 0;
int cupomUsado = 0;

float saldoInicial = 0;
float saldoCaixa = 0;
float totalVendas = 0;

float subtotalCompra = 0;
float descontoCompra = 0;
float totalCompra = 0;

void linha() {
    printf("+----------------------------------------------------------+\n");
}

void linhaMenor() {
    printf("+------------------------------------------------+\n");
}

void pausar() {
    int x;

    printf("\nDigite 0 para continuar: ");
    scanf("%d", &x);

    while (x != 0) {
        printf("Digite 0 para continuar: ");
        scanf("%d", &x);
    }
}

void cabecalho() {
    linha();
    printf("|          SISTEMA DE CAIXA DE SUPERMERCADO                |\n");
    printf("|          Hackathon em C - WYD6376                        |\n");
    printf("|          Prof. Kesede Rodrigues Julio                    |\n");
    linha();
}

void menuPrincipal() {
    cabecalho();
    printf("| 1 - Abrir o Caixa                                        |\n");
    printf("| 2 - Cadastrar Produto                                    |\n");
    printf("| 3 - Iniciar Compra                                       |\n");
    printf("| 4 - Emitir Cupom Fiscal                                  |\n");
    printf("| 5 - Fechar o Caixa                                       |\n");
    printf("| 6 - Sair                                                 |\n");
    linha();
    printf("Escolha: ");
}

int buscarProduto(int codigo) {
    int i;
    int posicao;

    posicao = -1;

    for (i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            posicao = i;
        }
    }

    return posicao;
}

void abrirCaixa() {
    if (caixaAberto == 1) {
        printf("\n[AVISO] O caixa ja esta aberto.\n");
    } else {
        printf("\nABERTURA DO CAIXA\n");
        linhaMenor();

        printf("Informe o saldo inicial: R$ ");
        scanf("%f", &saldoInicial);

        if (saldoInicial < 0) {
            printf("[ERRO] Valor invalido.\n");
        } else {
            saldoCaixa = saldoInicial;
            totalVendas = 0;
            quantidadeVendas = 0;
            caixaAberto = 1;

            printf("[OK] Caixa aberto com sucesso.\n");
        }
    }
}

void listarProdutos() {
    int i;

    printf("\nPRODUTOS CADASTRADOS\n");

    if (totalProdutos == 0) {
        printf("[AVISO] Nenhum produto cadastrado.\n");
    } else {
        printf("+--------+----------------------+----------+---------+\n");
        printf("| CODIGO | PRODUTO              | PRECO    | ESTOQUE |\n");
        printf("+--------+----------------------+----------+---------+\n");

        for (i = 0; i < totalProdutos; i++) {
            printf("| %-6d | %-20s | R$ %-5.2f | %-7d |\n",
                   produtos[i].codigo,
                   produtos[i].nome,
                   produtos[i].preco,
                   produtos[i].estoque);
        }

        printf("+--------+----------------------+----------+---------+\n");
    }
}

void cadastrarProduto() {
    int codigo;
    int posicao;

    if (totalProdutos >= 100) {
        printf("[ERRO] Limite maximo de produtos atingido.\n");
    } else {
        printf("\nCADASTRAR PRODUTO\n");
        linhaMenor();

        printf("Codigo: ");
        scanf("%d", &codigo);

        posicao = buscarProduto(codigo);

        if (posicao != -1) {
            printf("[ERRO] Ja existe produto com esse codigo.\n");
        } else {
            produtos[totalProdutos].codigo = codigo;

            printf("Nome sem espaco: ");
            scanf("%s", produtos[totalProdutos].nome);

            printf("Preco: R$ ");
            scanf("%f", &produtos[totalProdutos].preco);

            printf("Estoque: ");
            scanf("%d", &produtos[totalProdutos].estoque);

            if (produtos[totalProdutos].preco < 0) {
                printf("[ERRO] Preco invalido.\n");
            } else {
                if (produtos[totalProdutos].estoque < 0) {
                    printf("[ERRO] Estoque invalido.\n");
                } else {
                    totalProdutos++;
                    printf("[OK] Produto cadastrado com sucesso.\n");
                }
            }
        }
    }
}

void buscarProdutoTela() {
    int codigo;
    int posicao;

    if (totalProdutos == 0) {
        printf("[AVISO] Nenhum produto cadastrado.\n");
    } else {
        printf("\nBUSCAR PRODUTO\n");
        linhaMenor();

        printf("Digite o codigo: ");
        scanf("%d", &codigo);

        posicao = buscarProduto(codigo);

        if (posicao == -1) {
            printf("[ERRO] Produto nao encontrado.\n");
        } else {
            printf("+--------+----------------------+----------+---------+\n");
            printf("| CODIGO | PRODUTO              | PRECO    | ESTOQUE |\n");
            printf("+--------+----------------------+----------+---------+\n");
            printf("| %-6d | %-20s | R$ %-5.2f | %-7d |\n",
                   produtos[posicao].codigo,
                   produtos[posicao].nome,
                   produtos[posicao].preco,
                   produtos[posicao].estoque);
            printf("+--------+----------------------+----------+---------+\n");
        }
    }
}

void produtosEstoqueBaixo() {
    int i;
    int achou;

    achou = 0;

    printf("\nPRODUTOS COM ESTOQUE BAIXO\n");

    if (totalProdutos == 0) {
        printf("[AVISO] Nenhum produto cadastrado.\n");
    } else {
        printf("+--------+----------------------+----------+---------+\n");
        printf("| CODIGO | PRODUTO              | PRECO    | ESTOQUE |\n");
        printf("+--------+----------------------+----------+---------+\n");

        for (i = 0; i < totalProdutos; i++) {
            if (produtos[i].estoque <= 5) {
                printf("| %-6d | %-20s | R$ %-5.2f | %-7d |\n",
                       produtos[i].codigo,
                       produtos[i].nome,
                       produtos[i].preco,
                       produtos[i].estoque);
                achou = 1;
            }
        }

        printf("+--------+----------------------+----------+---------+\n");

        if (achou == 0) {
            printf("[OK] Nenhum produto com estoque baixo.\n");
        }
    }
}

void alterarProduto() {
    int codigo;
    int posicao;
    int opcao;

    if (totalProdutos == 0) {
        printf("[AVISO] Nenhum produto cadastrado.\n");
    } else {
        printf("\nALTERAR PRODUTO\n");
        linhaMenor();

        printf("Codigo do produto: ");
        scanf("%d", &codigo);

        posicao = buscarProduto(codigo);

        if (posicao == -1) {
            printf("[ERRO] Produto nao encontrado.\n");
        } else {
            printf("Produto encontrado: %s\n", produtos[posicao].nome);

            printf("\n1 - Alterar nome\n");
            printf("2 - Alterar preco\n");
            printf("3 - Alterar estoque\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Novo nome sem espaco: ");
                    scanf("%s", produtos[posicao].nome);
                    printf("[OK] Nome alterado.\n");
                    break;

                case 2:
                    printf("Novo preco: R$ ");
                    scanf("%f", &produtos[posicao].preco);

                    if (produtos[posicao].preco < 0) {
                        produtos[posicao].preco = 0;
                        printf("[AVISO] Preco invalido. Ajustado para zero.\n");
                    } else {
                        printf("[OK] Preco alterado.\n");
                    }
                    break;

                case 3:
                    printf("Novo estoque: ");
                    scanf("%d", &produtos[posicao].estoque);

                    if (produtos[posicao].estoque < 0) {
                        produtos[posicao].estoque = 0;
                        printf("[AVISO] Estoque invalido. Ajustado para zero.\n");
                    } else {
                        printf("[OK] Estoque alterado.\n");
                    }
                    break;

                default:
                    printf("[ERRO] Opcao invalida.\n");
            }
        }
    }
}

void menuProdutos() {
    int opcao;

    do {
        printf("\n");
        linhaMenor();
        printf("|               MENU DE PRODUTOS                 |\n");
        linhaMenor();
        printf("| 1 - Cadastrar produto                          |\n");
        printf("| 2 - Visualizar produtos                        |\n");
        printf("| 3 - Alterar produto                            |\n");
        printf("| 4 - Buscar produto por codigo                  |\n");
        printf("| 5 - Ver produtos com estoque baixo             |\n");
        printf("| 6 - Voltar                                     |\n");
        linhaMenor();
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto();
                pausar();
                break;

            case 2:
                listarProdutos();
                pausar();
                break;

            case 3:
                alterarProduto();
                pausar();
                break;

            case 4:
                buscarProdutoTela();
                pausar();
                break;

            case 5:
                produtosEstoqueBaixo();
                pausar();
                break;

            case 6:
                printf("Voltando ao menu principal.\n");
                break;

            default:
                printf("[ERRO] Opcao invalida.\n");
                pausar();
        }

    } while (opcao != 6);
}

void aplicarCupom() {
    int opcaoCupom;

    if (totalItens == 0) {
        printf("[ERRO] Carrinho vazio.\n");
    } else {
        printf("\nCUPONS DISPONIVEIS\n");
        printf("1 - Sem cupom\n");
        printf("2 - DESC10, 10 por cento\n");
        printf("3 - DESC20, 20 por cento acima de R$ 100.00\n");
        printf("Escolha: ");
        scanf("%d", &opcaoCupom);

        switch (opcaoCupom) {
            case 1:
                descontoCompra = 0;
                cupomUsado = 0;
                break;

            case 2:
                descontoCompra = subtotalCompra * 0.10;
                cupomUsado = 10;
                break;

            case 3:
                if (subtotalCompra >= 100) {
                    descontoCompra = subtotalCompra * 0.20;
                    cupomUsado = 20;
                } else {
                    descontoCompra = 0;
                    cupomUsado = 0;
                    printf("[AVISO] DESC20 so vale acima de R$ 100.00.\n");
                }
                break;

            default:
                descontoCompra = 0;
                cupomUsado = 0;
                printf("[ERRO] Opcao invalida. Nenhum cupom aplicado.\n");
        }

        totalCompra = subtotalCompra - descontoCompra;

        printf("Subtotal: R$ %.2f\n", subtotalCompra);
        printf("Desconto: R$ %.2f\n", descontoCompra);
        printf("Total:    R$ %.2f\n", totalCompra);
    }
}

void adicionarItem() {
    int codigo;
    int quantidade;
    int posicao;
    int i;

    if (totalItens >= 50) {
        printf("[ERRO] Limite de itens atingido.\n");
    } else {
        listarProdutos();

        printf("Codigo do produto: ");
        scanf("%d", &codigo);

        posicao = buscarProduto(codigo);

        if (posicao == -1) {
            printf("[ERRO] Produto nao encontrado.\n");
        } else {
            printf("Quantidade: ");
            scanf("%d", &quantidade);

            if (quantidade <= 0) {
                printf("[ERRO] Quantidade invalida.\n");
            } else {
                if (quantidade > produtos[posicao].estoque) {
                    printf("[ERRO] Estoque insuficiente.\n");
                } else {
                    carrinho[totalItens].codigo = produtos[posicao].codigo;

                    for (i = 0; produtos[posicao].nome[i] != '\0'; i++) {
                        carrinho[totalItens].nome[i] = produtos[posicao].nome[i];
                    }

                    carrinho[totalItens].nome[i] = '\0';
                    carrinho[totalItens].preco = produtos[posicao].preco;
                    carrinho[totalItens].quantidade = quantidade;
                    carrinho[totalItens].subtotal = quantidade * produtos[posicao].preco;

                    produtos[posicao].estoque = produtos[posicao].estoque - quantidade;

                    subtotalCompra = subtotalCompra + carrinho[totalItens].subtotal;
                    totalCompra = subtotalCompra;
                    descontoCompra = 0;
                    cupomUsado = 0;

                    totalItens++;

                    printf("[OK] Item adicionado ao carrinho.\n");
                }
            }
        }
    }
}

void visualizarCarrinho() {
    int i;

    if (totalItens == 0) {
        printf("[AVISO] Carrinho vazio.\n");
    } else {
        printf("\nCARRINHO DE COMPRAS\n");
        printf("+--------+----------------------+-----+----------+----------+\n");
        printf("| CODIGO | PRODUTO              | QTD | PRECO    | SUBTOTAL |\n");
        printf("+--------+----------------------+-----+----------+----------+\n");

        for (i = 0; i < totalItens; i++) {
            printf("| %-6d | %-20s | %-3d | R$ %-5.2f | R$ %-5.2f |\n",
                   carrinho[i].codigo,
                   carrinho[i].nome,
                   carrinho[i].quantidade,
                   carrinho[i].preco,
                   carrinho[i].subtotal);
        }

        printf("+--------+----------------------+-----+----------+----------+\n");
        printf("Subtotal: R$ %.2f\n", subtotalCompra);
        printf("Desconto: R$ %.2f\n", descontoCompra);
        printf("Total:    R$ %.2f\n", totalCompra);
    }
}

void removerItem() {
    int codigo;
    int i;
    int j;
    int achou;
    int posicaoProduto;

    achou = 0;

    if (totalItens == 0) {
        printf("[AVISO] Carrinho vazio.\n");
    } else {
        visualizarCarrinho();

        printf("Codigo do item para remover: ");
        scanf("%d", &codigo);

        for (i = 0; i < totalItens; i++) {
            if (carrinho[i].codigo == codigo) {
                achou = 1;

                posicaoProduto = buscarProduto(codigo);

                if (posicaoProduto != -1) {
                    produtos[posicaoProduto].estoque = produtos[posicaoProduto].estoque + carrinho[i].quantidade;
                }

                subtotalCompra = subtotalCompra - carrinho[i].subtotal;

                for (j = i; j < totalItens - 1; j++) {
                    carrinho[j] = carrinho[j + 1];
                }

                totalItens--;

                descontoCompra = 0;
                totalCompra = subtotalCompra;
                cupomUsado = 0;

                printf("[OK] Item removido. Cupom removido, se havia algum.\n");
            }
        }

        if (achou == 0) {
            printf("[ERRO] Item nao encontrado no carrinho.\n");
        }
    }
}

void cancelarCompra() {
    int i;
    int posicaoProduto;

    for (i = 0; i < totalItens; i++) {
        posicaoProduto = buscarProduto(carrinho[i].codigo);

        if (posicaoProduto != -1) {
            produtos[posicaoProduto].estoque = produtos[posicaoProduto].estoque + carrinho[i].quantidade;
        }
    }

    totalItens = 0;
    subtotalCompra = 0;
    descontoCompra = 0;
    totalCompra = 0;
    cupomUsado = 0;

    printf("[OK] Compra cancelada e estoque restaurado.\n");
}

void finalizarCompra() {
    int i;

    if (totalItens == 0) {
        printf("[ERRO] Nao ha itens para finalizar.\n");
    } else {
        aplicarCupom();

        totalItensUltimoCupom = totalItens;

        for (i = 0; i < totalItens; i++) {
            ultimoCupom[i] = carrinho[i];
        }

        saldoCaixa = saldoCaixa + totalCompra;
        totalVendas = totalVendas + totalCompra;
        quantidadeVendas++;

        printf("\nCOMPRA FINALIZADA\n");
        linhaMenor();
        printf("Subtotal: R$ %.2f\n", subtotalCompra);
        printf("Desconto: R$ %.2f\n", descontoCompra);
        printf("Total:    R$ %.2f\n", totalCompra);

        totalItens = 0;
        subtotalCompra = 0;
        descontoCompra = 0;
        totalCompra = 0;
    }
}

void iniciarCompra() {
    int opcao;

    if (caixaAberto == 0) {
        printf("[ERRO] Abra o caixa antes de iniciar uma compra.\n");
    } else {
        if (totalProdutos == 0) {
            printf("[ERRO] Cadastre produtos antes de iniciar uma compra.\n");
        } else {
            totalItens = 0;
            subtotalCompra = 0;
            descontoCompra = 0;
            totalCompra = 0;
            cupomUsado = 0;

            do {
                printf("\n");
                linhaMenor();
                printf("|                 NOVA COMPRA                    |\n");
                linhaMenor();
                printf("| 1 - Adicionar item                             |\n");
                printf("| 2 - Visualizar carrinho                        |\n");
                printf("| 3 - Remover item                               |\n");
                printf("| 4 - Aplicar cupom                              |\n");
                printf("| 5 - Finalizar compra                           |\n");
                printf("| 6 - Cancelar compra                            |\n");
                linhaMenor();
                printf("Escolha: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        adicionarItem();
                        pausar();
                        break;

                    case 2:
                        visualizarCarrinho();
                        pausar();
                        break;

                    case 3:
                        removerItem();
                        pausar();
                        break;

                    case 4:
                        aplicarCupom();
                        pausar();
                        break;

                    case 5:
                        finalizarCompra();
                        opcao = 6;
                        pausar();
                        break;

                    case 6:
                        cancelarCompra();
                        pausar();
                        break;

                    default:
                        printf("[ERRO] Opcao invalida.\n");
                        pausar();
                }

            } while (opcao != 6);
        }
    }
}

void emitirCupomFiscal() {
    int i;
    float subtotal;
    float desconto;
    float total;

    subtotal = 0;

    if (totalItensUltimoCupom == 0) {
        printf("[AVISO] Nenhuma compra finalizada.\n");
    } else {
        printf("\n");
        linhaMenor();
        printf("|                 CUPOM FISCAL                   |\n");
        linhaMenor();

        printf("+--------+----------------------+-----+----------+----------+\n");
        printf("| CODIGO | PRODUTO              | QTD | PRECO    | SUBTOTAL |\n");
        printf("+--------+----------------------+-----+----------+----------+\n");

        for (i = 0; i < totalItensUltimoCupom; i++) {
            printf("| %-6d | %-20s | %-3d | R$ %-5.2f | R$ %-5.2f |\n",
                   ultimoCupom[i].codigo,
                   ultimoCupom[i].nome,
                   ultimoCupom[i].quantidade,
                   ultimoCupom[i].preco,
                   ultimoCupom[i].subtotal);

            subtotal = subtotal + ultimoCupom[i].subtotal;
        }

        if (cupomUsado == 10) {
            desconto = subtotal * 0.10;
        } else {
            if (cupomUsado == 20) {
                desconto = subtotal * 0.20;
            } else {
                desconto = 0;
            }
        }

        total = subtotal - desconto;

        printf("+--------+----------------------+-----+----------+----------+\n");
        printf("Subtotal: R$ %.2f\n", subtotal);
        printf("Desconto: R$ %.2f\n", desconto);
        printf("Total:    R$ %.2f\n", total);
    }
}

void fecharCaixa() {
    if (caixaAberto == 0) {
        printf("[AVISO] O caixa ja esta fechado.\n");
    } else {
        printf("\nFECHAMENTO DO CAIXA\n");
        linhaMenor();
        printf("Saldo inicial:        R$ %.2f\n", saldoInicial);
        printf("Quantidade de vendas: %d\n", quantidadeVendas);
        printf("Total de vendas:      R$ %.2f\n", totalVendas);
        printf("Saldo final:          R$ %.2f\n", saldoCaixa);
        linhaMenor();

        caixaAberto = 0;

        printf("[OK] Caixa fechado com sucesso.\n");
    }
}

int main() {
    int opcao;

    do {
        menuPrincipal();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                abrirCaixa();
                pausar();
                break;

            case 2:
                menuProdutos();
                break;

            case 3:
                iniciarCompra();
                break;

            case 4:
                emitirCupomFiscal();
                pausar();
                break;

            case 5:
                fecharCaixa();
                pausar();
                break;

            case 6:
                if (caixaAberto == 1) {
                    printf("[AVISO] Feche o caixa antes de sair.\n");
                    opcao = 0;
                    pausar();
                } else {
                    printf("Encerrando o sistema.\n");
                }
                break;

            default:
                printf("[ERRO] Opcao invalida.\n");
                pausar();
        }

    } while (opcao != 6);

    return 0;
}