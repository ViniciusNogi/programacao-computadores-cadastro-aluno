
# Sistema de Cadastro e Gerenciamento de Alunos

Este projeto em linguagem C implementa um sistema simples para cadastro, atualização, listagem e exclusão de alunos, com base em suas notas (A1, A2 e AF), cálculo de média e status de aprovação.

## 🔧 Funcionalidades

- Cadastro de alunos com nome, RGM e notas (A1, A2).
- Cálculo automático da média e solicitação da AF se necessário.
- Atualização de dados do aluno (nome e notas).
- Exclusão de aluno pelo RGM.
- Listagem completa dos alunos cadastrados.
- Mensagens interativas e suporte a Windows e Linux.

## 📘 Como funciona o cálculo da média

- A média é a soma de A1 + A2.
- Caso a média seja menor que 6.0, o sistema solicita a nota da AF.
- A menor nota entre A1 e A2 é substituída pela AF.
- A nova média é recalculada.

## 💻 Execução

### Pré-requisitos
- Compilador C (como `gcc` no Linux ou o compilador do Code::Blocks no Windows).

### Compilação

```bash
gcc main.c -o sistema
```

### Execução

```bash
./sistema     # No Linux/macOS
sistema.exe   # No Windows
```

## 📂 Organização

- `main.c` — Arquivo principal contendo todo o código-fonte do sistema.
- `README.md` — Documentação do projeto.

## 🖥️ Compatibilidade

O código possui compatibilidade com **Windows e Linux**, incluindo comandos para limpar tela e pausa de forma adaptada:

```c
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif
```

```c
void pause() {
    #ifdef _WIN32
        system("pause");
    #else
        printf("Pressione ENTER para continuar...");
        while(getchar() != '\n');
        getchar();
    #endif
}
```


> Projeto acadêmico desenvolvido como exercício prático de lógica de programação em linguagem C.
