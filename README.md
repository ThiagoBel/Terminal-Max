# Terminal MAX
Terminal prático, curto e fácil de aprender os comandos, feito especialmente para ser fácil e não passar raiva no terminal.

Terminal com muitos comandos poderosos e fáceis de se usar.

> Funciona infelizmente apenas nas versões de Windows 10 ou versões mais atuais, ainda poderá rodar Windows 8 ou Windows 8.1, porém o terminal ficará MUITO feio, não é recomendado.

## Por que usar Terminal Max?
- Terminal simples com comandos curtos e fáceis de decorar.
- Com suporte ao CMD do Windows (comando: '*>*').
- Diferentes de alguns terminais, Terminal Max inicia no diretório do Desktop, caso não goste, poderá mudar o diretório usando o comando '*configs*' e indo até '*Diretório inicial*'.
- Suporte do Discord RPC (Podendo desativar ou ativar ela usando o comando '*configs*' e indo até '*Discord RPC*').
- Com suporte á imagens (ascii), com o comando:
```
define CAMINHO_DA_IMAGEM
image
```
ou
```
define CAMINHO_DA_IMAGEM &&&& image
```
- Caso se arrependa do Terminal Max, só usar o comando '*clear_cmd*' que limpará todos os rastros que o terminal deixou (até o path do sistema dele :o)
- Se você estiver num caminho distante e queira ir pro desktop, apenas use o comando: '*to_desktop*' e você será redirecionado para lá

## .trmax
.trmax é uma extenção de arquivo do próprio Terminal MAX, que serve para facilitar o uso do terminal.
### Como rodar ele?
Abra o TerminalMax.exe e execute o comando:
```run [NOMEDOARQUIVO].trmax```

Ou use a flag:
```"--run [NOMEDOARQUIVO].trmax"```

## Configurações
- Image chars (ASCII)
    - Serve para travar menos na hora da imagem por conta dos caracteres especiais
    - A qualidade fica meio ruim, porem otimizado

- Apelido
    - Chamaremos você pelo apelido que você selecionou OU pelo nome de usuario do windows

- Diretório inicial
    - Diretório que inicia o terminal (normalmente é o Desktop/Área de Trabalho)

- Discord RPC
    - Mostra para os outros que você está usando o Terminal Max

- Cor do prompt
    - Cor do prompt para deixar mais bonito, porém, como tem várias cores o prompt, pode demorar pra carregar o prompt.
    - Desativando a cor do prompt ficará MUITO mais rápido porém menos bonito

- PATH do sistema
    - Deixa usar flags mais fácilmente (TerminalMax --version , TerminalMax --run [NOME] , ...)

- Sons
    - Sons do sistema

- Todas as informações são todas salvas em `%LOCALAPPDATA%\TerminalMax`

## Operadores

Operadores são formas de enviar multiplos códigos em uma única linha

### Delay
Para fazer um operador de delay em milissegundos, apenas usar '*@@@@[VALOR]*', exemplo:
```
define Hello, World! @@@@1000 say
```

### Adição
Para fazer um operador de adição, apenas usar '*&&&&*', exemplo:
```
define Hello, World! &&&& say
```