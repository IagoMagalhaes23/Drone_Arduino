# Drone com microcontrolador Atmega328p


## Resumo
  <p> O presente repositório visa demonstrar todo o processo de construção de um drone modelo F450, descrevendo os passos realizados desde a seleção dos
materiais, desenvolvimento do sistema de controle PID, até chegar aos testes que incluem voo.
  Primeiro, será apresentado a definição da arquitetura, junto ao levantamento de requisitos e fluxograma de desenvolvimento que engloba todos os passos do
projeto. Logo depois, é apresentada a metodologia de desenvolvimento da PCB e o roteiro de testes aplicados para a sintonia do controle PID. </p>

### Definição da arquitetura
  A arquitetura do projeto se baseia no frame F450, que é um quadcóptero (aeronave impulsionada por quatro motores) muito popular na comunidade maker
devido ao seu baixo custo, facilidade de montagem e vasta comunidade. A figura 1 representa a estrutura deste frame em projeção 3d. <br>
![image](https://user-images.githubusercontent.com/65053026/234439795-296824c8-d95c-4d8a-9b34-0ea2acc1c069.png) <br>

### Levantamento dos requisitos
  Para o desenvolvimento do projeto serão necessários requisitos de hardware e software. Logo, o seguinte projeto tem como objetivo desenvolver um drone
utilizando Arduino como placa controladora, simulando modelos já existentes no mercado, objetivando reduzir custos e obter maior acesso a informações de
controle. O projeto ainda busca aplicar conhecimentos das áreas de sistemas de controle, eletrônica e computação.
  Além dos tópicos citados, o projeto utilizará a metodologia de setar os registradores do microcontrolador Atmega328p. Sendo a placa de controle baseada
no Arduino Nano, utilizaremos o sensor MPU 6050, led, rádio receptor e as saídas PWM. <br>
Como hardware, serão utilizado os seguintes componentes:
○ Frame F450;
○ ESC’s;
○ Motores brushless;
○ Hélices;
○ Bateria de LiPo de 12V;
○ Rádio receptor;
○ Rádio transmissor;
○ Placa de fenolite;
○ Arduino Nano;
○ MPU 6050;
○ Led;
○ Barra de pinos macho;
○ Barra de pinos fêmea;
○ Resistores;
○ Diodo 1N4007;
○ Jumpers.
E como funcionalidades principais do software:
○ Controlar velocidade dos motores brushless via PWM;
○ Receber dados via rádio;
○ Coletar informações do sensor MPU6050;
○ Realizar estabilidade durante o voo via controle PID;

### Fluxograma de desenvolvimento
  A figura 2, mostra o fluxograma detalhado onde é exemplificado o processo de desenvolvimento do projeto. Levando em consideração o acerto e o fracasso de
cada etapa. Caso alguma das etapas não saia como planejado, deveremos analisar os erros e realizar uma nova tentativa da mesma, para que haja a certeza de que
todos os critérios pré estabelecidos serão cumpridos. <br>
![image](https://user-images.githubusercontent.com/65053026/234439964-f0f444e3-882b-4365-a432-9fd48de26cb5.png) <br>

### Metodologia
#### Montagem da placa padrão
  Como forma de validar o hardware que será utilizado no desenvolvimento do protótipo, utilizamos uma placa padrão. A placa padrão consiste na montagem do
circuito em uma protoboard/placa perfurada a fim de testar os componentes eletrônicos. Ela possui como vantagem a montagem rápida e simplificada do
hardware final, sendo possível avaliar e testar configurações, ligações e software de forma eficiente. <br>
  A placa padrão utilizada para validar os componentes e software do drone foi montada na protoboard. A figura 03 mostra todos os componentes alocados em
suas posições no frame F450. A ligação do circuito foi feita por jumpers. Já a alimentação do circuito também foi fornecida pela bateria LiPo de 12V. <br>
![image](https://user-images.githubusercontent.com/65053026/234440094-60839471-411d-478b-944f-e9474757cfa8.png) <br>

#### Desenvolvimento da PCB
  Após a validação do circuito proposto na placa padrão, é feita a montagem do circuito em software de desenho de PCB’s. A equipe optou pelo Eagle como
software de desenvolvimento da placa de circuito impresso. <br>
O esquemático e o desenho final da PCB podem ser visualizados nas imagens abaixo. <br>
![image](https://user-images.githubusercontent.com/65053026/234440318-ffc7500f-9fa9-47a2-a755-5a429b1d5120.png) <br>
![image](https://user-images.githubusercontent.com/65053026/234440338-9d431dd1-5b00-4ef4-9de7-a7d474ee9620.png) <br>
  O processo de confecção utilizado foi o térmico, devido a sua facilidade e recursos acessíveis. Uma case foi desenvolvida para fixar a placa de controle no
frame do drone. A figura 06 representa o resultado final da placa fixada no frame do drone. <br>
![image](https://user-images.githubusercontent.com/65053026/234440425-a8b72427-494f-4778-8646-734d012cafdb.png) <br>

#### Reprodução do exemplo base
  Drones possuem certas características, como por exemplo, três eixos, o roll, pitch e yaw. Além de poderem se movimentar para cima, baixo, frente, atrás,
esquerda e direita. Essas características dificultam criar um software de controle simples, porém existem outras peculiaridades, como a necessidade de calibração
dos ESC’s, do sensor MPU6050 e das hélices. Cada um desses elementos possuem um papel fundamental no funcionamento do equipamento e necessitam dos devidos cuidados. <br>
  Existem muitos modelos controlados por Arduino, a internet é repleta de conteúdos de como criar seu próprio drone utilizando essa plataforma. Porém, um
tutorial criado por Joop Brokking tem bastante renome na comunidade quando se fala em drones controlados por Arduino. O trabalho de Brokking possui bastantes
citações no fórum oficial do Arduino, diversos tutoriais são baseados em seu projeto no YouTube e outros incontáveis fóruns pela Web, acreditamos que este seja uma
referência que deva ser seguida pelo seu prestígio e facilidade de implementação. <br>
  Em [10], é disponibilizado softwares que realizam a calibração dos adereços do equipamento. Seguindo o tutorial, [10] mostra como realizar a calibração do
controle (rádio) e do sensor MPU, através de um sketch simples. Nesse momento é feita a aquisição de todas as posições dos sticks e o teste da comunicação com o
controle via rádio. Depois, é feita a calibração precisa do sensor MPU que utiliza as portas I2C do microcontrolador, a uma frequência de 400 kHz, este verifica as
posições dos três eixos necessários no equipamento, sendo o roll, pitch e yaw. Para isso, movimentamos o frame em posições específicas para realizar as leituras. O
primeiro deles é movimentar o frame em 45° lateralmente, depois 45° levantando a parte frontal e por fim, girando o frame em 90° no seu próprio eixo, essas posições e
leituras são gravadas na memória EEPROM para utilização futura durante o voo. <br>
  Após a calibração do sensor e controle, é necessário regular a velocidade dos ESC’s, para que os mesmos girem na mesma velocidade e assim seja possível
ter um voo estável e controlado. O processo de regulação também é citado em [10], porém, o fabricante também descreve o processo em seu datasheet, que é bem
simples. Basta movimentar o stick de velocidade para o máximo e conectar a bateria ao drone, após uma sequência de bips movemos o stick para a posição mínima e
aguardamos um bip longo. Depois, removemos a bateria e conectamos novamente, agora é possível notar que ao acionar os motores, os mesmos giram na mesma
velocidade. <br>
  O último passo é calibração das hélices, através de um sketch fornecido por [10], é possível ver a vibração causada pelo motor e hélice da estrutura do
dispositivo. Isso ocorre porque os motores giram em alta velocidade e as hélices não são balanceadas. A forma encontrada para solucionar o problema do
desbalanceamento é colocando um pequeno pedaço de fita na hélice e executando o script para analisar a vibração que ela exerce no frame até que se reduza o
máximo possível, inserindo mais pedaços se necessário. <br>

#### DESENVOLVIMENTO DO SOFTWARE
O código fonte utilizado na controladora de voo do drone foi desenvolvido utilizando a linguagem C. Com o objetivo de simplificar o projeto final, apenas o script de controle de voo será comentado, já que ele foi desenvolvido com as modificações necessárias pela equipe.
O código final utilizou basicamente as bibliotecas EEPROM e Wire, sendo estas para ler a memória EEPROM e para comunicação I2C. Nas definições de pinos, o PORTD foi utilizado para controle dos ESC’s e o PORTB para o receptor e led de indicação de status.
Ao iniciar o software, os seguintes passos serão realizados:
1.  Leitura do conteúdo da memória EEPROM, que armazena as leituras do sensor na etapa de calibração;
2.  Armazenamento do endereço do sensor MPU6050;
3.  Definição da velocidade de comunicação do I2C em 400 kHz;
4.  Set dos pinos 4, 5, 6 e 7 do PORTD como saída;
5.  Set dos pinos 12 e 13 do PORTB como saída;18
6.  Acenderá o led;
7.  Configuração dos registradores do sensor MPU6050;
8.  Realização da calibração do sensor, capturando 2000 amostras. O led ficará piscando durante o processo, que leva de 5 a 10 segundos;
9.  Ativação da varredura PCMSK0 para disparar interrupções nos pinos 8, 9, 10 e 11;
10. Verificação para observar se o stick de velocidade está em zero;
11. Leitura da tensão da bateria;
12. Desligamento do led;
13. Leitura das posições em roll, pitch e yaw através do sensor;
14. Atualização dos valores de cálculo do PID;
15. Verificação das posições do stick para armar o drone;
16. Leitura da tensão da bateria;
17. Leitura das posições dos stick’s;
18. Envio de pulsos para os ESC’s.
Para realizar as interrupções, cálculo do PID, ler dados do sensor, ler dados
do rádio e para setar os registradores do sensor, foram utilizadas funções. A primeira delas é a interrupção PCINT0, para que toda vez que um valor for lido pelo rádio, ela entrará e a atualizará o valor da posição do stick. A segunda função realiza os cálculos do controle PID, através das leituras das posições do stick e do sensor, a função de controle tenta deixar o drone o mais estável possível. A próxima função, realiza a leitura de valores do sensor usando a biblioteca Wire. A função de leitura de dados do rádio, realiza conversões e atualizações das posições dos sticks em caso de ligações invertidas e transforma o valor da posição em pulsos que podem variar de 1000us até 2000us. E por fim, a função que seta os registradores do sensor MPU6050.

#### SINTONIA DOS PARÂMETROS PID
Os valores de PID foram obtidos por meio de testes de tentativa e erro. No começo, fizemos um teste com os parâmetros default do código, mas esses parâmetros não conseguiram estabilizar o nosso sistema como esperado, já que todo sistema possui suas particularidades. Então, zeramos todos os valores e ligamos o drone para observar seu comportamento e conseguir analisar quais valores deveriam ser incrementados ou decrementados, conforme os testes.
Esse processo requer uma rotina árdua de testes, devido ao método de sintonia adotado. Requerendo paciência e bastante observação as mudanças que ocorrem quando os valores de P, I e D são alterados no script. Sendo assim, é necessário realizar uma análise visual para determinar quais combinações atingiram melhores resultados e quais aspectos e propriedades poderiam ser alterados, em busca de melhorias.
Por fim, após uma longa sequência de testes e análises, foi possível utilizar nos eixos roll e pitch os valores de P = 1.0, I = 0.00001 e D = 0.0. Já no eixo yaw os valores ficaram em P = 0.0, I = 0.0 e D = 0.0, ou seja, sem aplicação do controle PID neste eixo.

#### ROTINA DE TESTES
Inicialmente, realizamos testes em laboratório, porém esses testes não foram bem sucedidos pois não tínhamos uma base de fixação para colocar o drone e o mesmo estava inclinando e indo para frente quando tentamos levantar voo. Então optamos  por  construir  uma  base  para  que  fosse  possível  fixar  e  testar  os movimentos de voo.

![image](https://github.com/IagoMagalhaes23/Drone_Arduino/assets/65053026/339eefca-90d8-4801-ac89-d74bc3d99189)

Os primeiros testes com a base foram feitos em ambiente sem interferência externa de vento, as perturbações causadas durante o voo foram feitas por nós mesmos, apenas balançando um pouco o drone para conseguir ajustar os valores de PID.
Outro teste foi realizado colocando um cabo de vassoura no meio da carcaça do drone para ver se ele continuaria estável com o aumento de peso e para causarmos maiores perturbações sem o risco de o mesmo girar e quebrar algum componente. Nesse teste percebemos que ele tentava e até conseguia ficar estável por um curto período, mas logo desestabilizava, então fizemos alguns ajustes nos valores de D.
Após os testes anteriores, decidimos ver como nosso drone se comportaria em uma base em que ele tivesse maior liberdade de voo e com interferência de vento, representada na figura 15. Então fomos para uma área externa e percebemos que os valores de PID que ajustamos para o ambiente anterior não estavam conseguindo estabilizar o drone no novo ambiente de testes. Tentamos fazer alguns ajustes nos parâmetros, mas como não conseguimos estabilizá-lo com base nos parâmetros anteriores, decidimos refazer os testes de estabilização de tentativa e erro para as novas circunstâncias.

![image](https://github.com/IagoMagalhaes23/Drone_Arduino/assets/65053026/f255293c-bcf1-4361-907f-a426a50688e5)

A partir daí, foi mais difícil achar os valores de PID, pois o drone tinha mais mobilidade e o vento atrapalhava bastante. Então decidimos fazer uma calibração mais genérica, ou seja, a estabilidade do drone não seria tão boa, mas dessa forma ele conseguiria se estabilizar mesmo quando houvesse um vento mais forte, ou caso houvesse uma batida forte durante o pouso. E para cada teste aumentamos um pouco a corda que amarrava o drone, para ver como ele se comportava em diferentes alturas e consequentemente com maior grau de liberdade.
E para os testes finais, levamos o drone para um espaço onde o chão fosse macio e não houvesse obstáculos, para que ele pudesse voar livremente e caso ele caísse, os danos seriam leves. Nesse teste, também prendemos o drone com uma corda, porém dessa vez a corda era bem maior e servia apenas como precaução para ele não ir muito alto. Infelizmente não obtivemos sucesso no último teste, pois como nossa PCB havia quebrado e nessa fase o circuito estava montado em uma protoboard, creio que ela não estava suportando a demanda de corrente e conexões utilizando jumpers apresentavam falhas quando o vento gerado pelas hélices ficava mais forte.

### CONCLUSÃO
Com base nos resultados obtidos por meio dos testes, percebe-se que o trabalho proposto necessita de bastante tempo e dedicação para realizar seus testes e para pesquisar vários métodos diferentes que possam solucionar os problemas que surgem no meio do processo. Pois mesmo utilizando um trabalho bem detalhado como base, as situações de teste e de desenvolvimento acabam nunca sendo as mesas, portanto problemas diferentes surgem e são solucionados de maneiras bem diferentes das que foram utilizadas.
A conclusão desta etapa é que, conseguimos levantar voo e manter estabilidade mesmo com interferência do vento. Quando tentamos realizar algumas curvas o sistema consegue continuar estável, mas se no retorno para o ponto inicial o drone passar por alguma interferência ele sofre uma desestabilização, mas retorna ao normal em um curto período. Os requisitos de hardware e software foram atendidos, porém, os parâmetros de controle PID ainda podem ser melhorados e ficará como sugestão de melhoria em um possível trabalho futuro.

### BIBLIOGRAFIA
[1] O QUE são drones e quais regras você precisa seguir para pilotar no Brasil. [S. l.], 10 dez. 2013. Disponível em: https://tecnoblog.net/responde/tudo-sobre-drones/. Acesso em: 10 dez. 2022. <br>
[2] PROJETO DE DRONE DE BAIXO CUSTO PARA MONITORAMENTO EM ÁREAS AGRÍCOLAS. 2021. Monografia (Bacharel em Engenharia de Biossistemas) - Trabalho de Conclusão de Curso, [S. l.], 2021. <br>
[3] ANATOMIA de um Drone. [S. L.] Disponível em: https://www.flypro.com.br/pagina/anatomia-de-um-drone.html#:~:text=Drones%20(q uadric%C3%B3pteros)%20tem%202%20motores,oposta%20e%20de%20mesma% 20intensidade. Acesso em: 10 dez. 2022. <br>
[4] INTRODUÇÃO aos drones: O que são e como funcionam os drones?. [S. l.], 17 ago. 2020. Disponível em: https://www.filipeflop.com/blog/o-que-e-como-funciona-um-drone/.  Acesso  em:  10 dez. 2022. <br>
[5] CONTROLE PID: rompendo a barreira do tempo. [S. l.], 9 jun. 2020. Disponível em: https://www.novus.com.br/blog/artigo-controle-pid-rompendo-a-barreira-do-tempo/. Acesso em: 10 dez. 2022. <br>
[6] SISTEMAS de controle : princípios e métodos de projeto. In: SISTEMAS de controle : princípios e métodos de projeto. [S. l.: s. n.], 2005. <br>
[7] ANATOMIA de um Drone [S. L.]. Disponível em: https://www.flypro.com.br/pagina/anatomia-de-um-drone.html#:~:text=A%20controla dora%20de%20voo%20recebe,um%20dia%20de%20muito%20vento. Acesso em: 10 dez. 2022. <br>
[8] ACELERÔMETRO e Giroscópio MPU6050. [S. l.], 28 abr. 2015. Disponível em: https://www.arduinoecia.com.br/acelerometro-giroscopio-mpu6050-arduino/. Acesso em: 11 dez. 2022. <br>
[9] TUTORIAL: Acelerômetro MPU6050 com Arduino. [S. l.], 30 set. 2014. Disponível em: https://www.filipeflop.com/blog/tutorial-acelerometro-mpu6050-arduino/. Acesso em: 11 dez. 2022. <br>
[10] Project YMFC-AL - The Arduino auto-level quadcopter. [S. I.], 30 abr. 2017. Disponível em: http://www.brokking.net/ymfc-al_main.html. Acesso em: 11 dez. 2022. <br>
