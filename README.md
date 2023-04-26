# Drone com microcontrolador Atmega328p


## Resumo
  O presente repositório visa demonstrar todo o processo de construção de um drone modelo F450, descrevendo os passos realizados desde a seleção dos
materiais, desenvolvimento do sistema de controle PID, até chegar aos testes que incluem voo.
Primeiro, será apresentado a definição da arquitetura, junto ao levantamento de requisitos e fluxograma de desenvolvimento que engloba todos os passos do
projeto. Logo depois, é apresentada a metodologia de desenvolvimento da PCB e o roteiro de testes aplicados para a sintonia do controle PID.

### Definição da arquitetura
  A arquitetura do projeto se baseia no frame F450, que é um quadcóptero (aeronave impulsionada por quatro motores) muito popular na comunidade maker
devido ao seu baixo custo, facilidade de montagem e vasta comunidade. A figura 1 representa a estrutura deste frame em projeção 3d.
![image](https://user-images.githubusercontent.com/65053026/234439795-296824c8-d95c-4d8a-9b34-0ea2acc1c069.png)

### Levantamento dos requisitos
  Para o desenvolvimento do projeto serão necessários requisitos de hardware e software. Logo, o seguinte projeto tem como objetivo desenvolver um drone
utilizando Arduino como placa controladora, simulando modelos já existentes no mercado, objetivando reduzir custos e obter maior acesso a informações de
controle. O projeto ainda busca aplicar conhecimentos das áreas de sistemas de controle, eletrônica e computação.
  Além dos tópicos citados, o projeto utilizará a metodologia de setar os registradores do microcontrolador Atmega328p. Sendo a placa de controle baseada
no Arduino Nano, utilizaremos o sensor MPU 6050, led, rádio receptor e as saídas PWM.
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
todos os critérios pré estabelecidos serão cumpridos.
![image](https://user-images.githubusercontent.com/65053026/234439964-f0f444e3-882b-4365-a432-9fd48de26cb5.png)

### Metodologia
#### Montagem da placa padrão
  Como forma de validar o hardware que será utilizado no desenvolvimento do protótipo, utilizamos uma placa padrão. A placa padrão consiste na montagem do
circuito em uma protoboard/placa perfurada a fim de testar os componentes eletrônicos. Ela possui como vantagem a montagem rápida e simplificada do
hardware final, sendo possível avaliar e testar configurações, ligações e software de forma eficiente.
  A placa padrão utilizada para validar os componentes e software do drone foi montada na protoboard. A figura 03 mostra todos os componentes alocados em
suas posições no frame F450. A ligação do circuito foi feita por jumpers. Já a alimentação do circuito também foi fornecida pela bateria LiPo de 12V.
![image](https://user-images.githubusercontent.com/65053026/234440094-60839471-411d-478b-944f-e9474757cfa8.png)

#### Desenvolvimento da PCB
  Após a validação do circuito proposto na placa padrão, é feita a montagem do circuito em software de desenho de PCB’s. A equipe optou pelo Eagle como
software de desenvolvimento da placa de circuito impresso.
O esquemático e o desenho final da PCB podem ser visualizados nas imagens abaixo.
![image](https://user-images.githubusercontent.com/65053026/234440318-ffc7500f-9fa9-47a2-a755-5a429b1d5120.png)
![image](https://user-images.githubusercontent.com/65053026/234440338-9d431dd1-5b00-4ef4-9de7-a7d474ee9620.png)
  O processo de confecção utilizado foi o térmico, devido a sua facilidade e recursos acessíveis. Uma case foi desenvolvida para fixar a placa de controle no
frame do drone. A figura 06 representa o resultado final da placa fixada no frame do drone.
![image](https://user-images.githubusercontent.com/65053026/234440425-a8b72427-494f-4778-8646-734d012cafdb.png)

#### Reprodução do exemplo base
  Drones possuem certas características, como por exemplo, três eixos, o roll, pitch e yaw. Além de poderem se movimentar para cima, baixo, frente, atrás,
esquerda e direita. Essas características dificultam criar um software de controle simples, porém existem outras peculiaridades, como a necessidade de calibração
dos ESC’s, do sensor MPU6050 e das hélices. Cada um desses elementos possuem um papel fundamental no funcionamento do equipamento e necessitam dos devidos cuidados.
  Existem muitos modelos controlados por Arduino, a internet é repleta de conteúdos de como criar seu próprio drone utilizando essa plataforma. Porém, um
tutorial criado por Joop Brokking tem bastante renome na comunidade quando se fala em drones controlados por Arduino. O trabalho de Brokking possui bastantes
citações no fórum oficial do Arduino, diversos tutoriais são baseados em seu projeto no YouTube e outros incontáveis fóruns pela Web, acreditamos que este seja uma
referência que deva ser seguida pelo seu prestígio e facilidade de implementação.
  Em [10], é disponibilizado softwares que realizam a calibração dos adereços do equipamento. Seguindo o tutorial, [10] mostra como realizar a calibração do
controle (rádio) e do sensor MPU, através de um sketch simples. Nesse momento é feita a aquisição de todas as posições dos sticks e o teste da comunicação com o
controle via rádio. Depois, é feita a calibração precisa do sensor MPU que utiliza as portas I2C do microcontrolador, a uma frequência de 400 kHz, este verifica as
posições dos três eixos necessários no equipamento, sendo o roll, pitch e yaw. Para isso, movimentamos o frame em posições específicas para realizar as leituras. O
primeiro deles é movimentar o frame em 45° lateralmente, depois 45° levantando a parte frontal e por fim, girando o frame em 90° no seu próprio eixo, essas posições e
leituras são gravadas na memória EEPROM para utilização futura durante o voo.
  Após a calibração do sensor e controle, é necessário regular a velocidade dos ESC’s, para que os mesmos girem na mesma velocidade e assim seja possível
ter um voo estável e controlado. O processo de regulação também é citado em [10], porém, o fabricante também descreve o processo em seu datasheet, que é bem
simples. Basta movimentar o stick de velocidade para o máximo e conectar a bateria ao drone, após uma sequência de bips movemos o stick para a posição mínima e
aguardamos um bip longo. Depois, removemos a bateria e conectamos novamente, agora é possível notar que ao acionar os motores, os mesmos giram na mesma
velocidade.
  O último passo é calibração das hélices, através de um sketch fornecido por [10], é possível ver a vibração causada pelo motor e hélice da estrutura do
dispositivo. Isso ocorre porque os motores giram em alta velocidade e as hélices não são balanceadas. A forma encontrada para solucionar o problema do
desbalanceamento é colocando um pequeno pedaço de fita na hélice e executando o script para analisar a vibração que ela exerce no frame até que se reduza o
máximo possível, inserindo mais pedaços se necessário.

