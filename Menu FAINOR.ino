#include <U8glib.h>

    /*-----------------------------------------------------------------------------------
   *                              JOGO PONG: DEFINIÇÕES
   ------------------------------------------------------------------------------------*/
   
// Definir o pino do joystick x e y
#define JOY1_X_PIN A0
#define JOY1_Y_PIN A1
#define JOY2_X_PIN A2
#define JOY2_Y_PIN A3

// Definir as variáveis para a posição do jogador
int player1_pos = 30;
int player2_pos = 30;

// Definir as variáveis de bola
int ball_x = 63;
int ball_y = 31;
int ball_dx = 1;
int ball_dy = 1;

// Definir a variável de pontuação
int score1 = 0;
int score2 = 0;

    /*-----------------------------------------------------------------------------------
   *                              JOGO PONG: FIM DEFINIÇÕES
   ------------------------------------------------------------------------------------*/

// NOTA IMPORTANTE: A lista completa de dispositivos suportado por esta biblioteca está disponível em: https://github.com/olikraus/u8glib/wiki

U8GLIB_ST7920_128X64_1X u8g(5, 4, 3 ,6); //Configura o LCD para os rescpectivos pinos Enable, RW, RS, RESET  

#define BOT_TEMP 0        //Valor temporário

 /*-----------------------------------------------------------------------------------
   *   Abaixo está os respectivos Botões para a navegação - XProjetos.net
   *   Só alterar o numero do respectivo pino de saída do Botão (Usar o GND nos botões)
   ------------------------------------------------------------------------------------*/

#define BOT_VOLTAR 8
#define BOT_AVANCAR 9
#define BOT_SELECIONAR 10
#define BOT_VOLTAR_MENU 11

uint8_t IHM_Botao_Voltar = 8;
uint8_t IHM_Botao_Avancar = 9;
uint8_t IHM_Botao_Selecionar = 10;
uint8_t IHM_Botao_VoltarMenu = 11;


uint8_t uiKeyCodeFirst = BOT_TEMP;
uint8_t uiKeyCodeSecond = BOT_TEMP;
uint8_t uiKeyCode = BOT_TEMP;


void IMH_Config(void) {
  // Configuração dos Botões de Comando 
  pinMode(IHM_Botao_Voltar, INPUT);               // Configura o pino como entrada
  digitalWrite(IHM_Botao_Voltar, HIGH);           // Habilita o resistor de pullup interno
  pinMode(IHM_Botao_Avancar, INPUT);              // Configura o pino como entrada
  digitalWrite(IHM_Botao_Avancar, HIGH);          // Habilita o resistor de pullup interno
  pinMode(IHM_Botao_Selecionar, INPUT);           // Configura o pino como entrada
  digitalWrite(IHM_Botao_Selecionar, HIGH);       // Habilita o resistor de pullup interno
  pinMode(IHM_Botao_VoltarMenu, INPUT);           // Configura o pino como entrada
  digitalWrite(IHM_Botao_VoltarMenu, HIGH);       // Habilita o resistor de pullup interno
}

void IMH_Debounce(void) {
   // Debounce dos botões                    
  uiKeyCodeSecond = uiKeyCodeFirst;
  if ( digitalRead(IHM_Botao_Voltar) == LOW )
    uiKeyCodeFirst = BOT_VOLTAR;
  else if ( digitalRead(IHM_Botao_Avancar) == LOW )
    uiKeyCodeFirst = BOT_AVANCAR;
  else if ( digitalRead(IHM_Botao_Selecionar) == LOW )
    uiKeyCodeFirst = BOT_SELECIONAR;
  else if ( digitalRead(IHM_Botao_VoltarMenu) == LOW )
    uiKeyCodeFirst = BOT_VOLTAR_MENU;
  else 
    uiKeyCodeFirst = BOT_TEMP;
  
  if ( uiKeyCodeSecond == uiKeyCodeFirst )
    uiKeyCode = uiKeyCodeFirst;
  else
    uiKeyCode = BOT_TEMP;
}


#define MENU_ITEMS 5                  //Conforme o numero de menus é necessário altera-lo
char *menu_strings[MENU_ITEMS] = { "Primeiro Menu", "Segundo Menu", "Terceiro Menu", "Jogo Pong", "FAINOR 2023" };     //Os nomes dos menus que irão aparecer no Display

uint8_t menu_atualmente = 0;          //Verifica a tela atual ue está sendo exibida
uint8_t menu_chamada_menu = 0;        //Habilita que o menu seja redesenhado na tela
uint8_t last_key_code = BOT_TEMP;
int tela = 0;                         //Valor da tela que está sendo exibida atualmente


 /*-----------------------------------------------------------------------------------
   *   Abaixo segue as Subrotinas referente a cada tela do menu (Todas são exemplos) - XProjetos.net
   *   Basta criar um Void Tela() para sua tela
   ------------------------------------------------------------------------------------*/

void Tela1()                        //Tela 1 - Caracteres Ascii - Pag. 1  
{
  char s[2] = " ";  
  u8g.drawStr( 0, 0, "ASCII page 1");  
  for(int y = 0; y < 6; y++ ) 
  {  
    for(int x = 0; x < 16; x++ ) 
    {
      s[0] = y*16 + x + 32;  
      u8g.drawStr(x*7, y*10+10, s);  
    }  
  }  
}

void Tela2(void) {                  // Desenha um relogio estático na tela
    //u8g.drawRFrame(0,0,128,64,3);  
  u8g.drawStr( 3, 10, "Hor.: 15:00");  
  u8g.drawStr( 3, 25, "Temp: 45");  
  char s[2] = " ";  
  s[0] = 176;  
  u8g.drawStr(51, 25, s);  
  u8g.drawStr( 3, 40, "Umid: 25%"); 
  u8g.drawStr( 3, 55, "FAINOR 2023");  
  u8g.drawCircle(95,32,28);  
  u8g.drawCircle(95,32,29);  
  u8g.drawLine(95, 9, 95, 4);  
  u8g.drawLine(123, 32, 118, 32);  
  u8g.drawLine(95, 55, 95, 60);  
  u8g.drawLine(67, 32, 72, 32);  
  u8g.drawLine(95, 32, 95, 12);  
  u8g.drawLine(95, 32, 100.8, 21.87 );  
  u8g.setFont(u8g_font_04b_03);  
  u8g.drawStr(89,43, "Tag");  
  u8g.drawStr(75,50, "FAINOR 2023"); 
}

void Tela3()  {                      //Tela 3 - Teste
  char s[2] = " ";  
  u8g.drawStr( 12, 12, "Faculdade"); //(Coluna, Linha, Texto);
  u8g.drawStr( 12, 22, "Independente");
  u8g.drawStr( 12, 32, "do Nordeste");   
  u8g.drawLine(120, 4, 120, 60); //(Coluna Inicial,Linha Inicial,Coluna Final,Linha Final)(128x64);
  u8g.drawLine(8, 60, 120, 60); 
  u8g.drawLine(8, 4, 120, 4);
  u8g.drawLine(8, 4, 8, 60);
}

void Tela4()  {                      //Tela 4 - Pong
// Limpar a tela
clear_screen();

// Atualizar as posições dos jogadores e da bola
update_player1();
update_player2();
update_ball();

// Desenhar os jogadores, a bola e a pontuação
draw_player1();
draw_player2();
draw_ball();
draw_score();

// Atualizar o display
u8g.firstPage();
do {
draw_player1();
draw_player2();
draw_ball();
draw_score();
} while (u8g.nextPage());

// Aguardar um pouco para diminuir a velocidade do jogo
delay(10);   
}

    /*-----------------------------------------------------------------------------------
   *                              JOGO PONG: FUNÇÕES
   ------------------------------------------------------------------------------------*/

void DesenharMenu(void) {  // Abaixo está a subrotina de desenho do menu principal
  uint8_t i, h;
  u8g_uint_t w, d;

  u8g.setFont(u8g_font_6x13);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  //XProjetos.net
  h = u8g.getFontAscent()-u8g.getFontDescent();
  w = u8g.getWidth();
  for( i = 0; i < MENU_ITEMS; i++ ) {
    d = (w-u8g.getStrWidth(menu_strings[i]))/2;
    u8g.setDefaultForegroundColor();
    if ( i == menu_atualmente ) {
      u8g.drawBox(10, i*h+1, 110, h);
      u8g.setDefaultBackgroundColor();
    }
    u8g.drawStr(d, i*h, menu_strings[i]);
  }
}

void AtualizarMenu(void) { // Função para troca de linha do itens do menu
  if ( uiKeyCode != BOT_TEMP && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;
  
  switch ( uiKeyCode ) {
    case BOT_AVANCAR:
      menu_atualmente++;
      if ( menu_atualmente >= MENU_ITEMS )
        menu_atualmente = 0;
      //menu_chamada_menu = 0;
      break;
    case BOT_VOLTAR:
      if ( menu_atualmente == 0 )
        menu_atualmente = MENU_ITEMS;
      menu_atualmente--;
      break;
  }
}

// Função para desenhar o jogador 1
void draw_player1() {
  u8g.drawBox(3, player1_pos, 3, 15);
}

// Função para desenhar o jogador 2
void draw_player2() {
  u8g.drawBox(122, player2_pos, 3, 15);
}

// Função para desenhar a bola
void draw_ball() {
  u8g.drawCircle(ball_x, ball_y, 2);
}

// Função para desenhar a pontuação
void draw_score() {
  char score_str[10];
  sprintf(score_str, "%d - %d", score1, score2);
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(53, 8, score_str);
}

// Função para atualizar a posição do jogador 1
void update_player1() {
  int joy_x = analogRead(JOY1_X_PIN);
  int joy_y = analogRead(JOY1_Y_PIN);
  player1_pos = map(joy_y, 0, 1023, 0, 49);
}

// Função para atualizar a posição do jogador 2
void update_player2() {
  int joy_x = analogRead(JOY2_X_PIN);
  int joy_y = analogRead(JOY2_Y_PIN);
  player2_pos = map(joy_y, 0, 1023, 0, 49);
}

// Função para atualizar a posição da bola
void update_ball() {
  ball_x += ball_dx;
  ball_y += ball_dy;

  // Verificar colisão com os jogadores
  if (ball_x < 10 && ball_y > player1_pos && ball_y < player1_pos + 15) {
    ball_dx = -ball_dx;
  }
  if (ball_x > 118 && ball_y > player2_pos && ball_y < player2_pos + 15) {
    ball_dx = -ball_dx;
  }

  // Verificar colisão com as paredes superior e inferior
  if (ball_y < 2 || ball_y > 62) {
    ball_dy = -ball_dy;
  }

  // Verificar se a bola saiu do campo
  if (ball_x < 2) {
    score2++;
    ball_x = 63;
    ball_y = 31;
    ball_dx = -ball_dx;
  }
  if (ball_x > 126) {
    score1++;
    ball_x = 63;
    ball_y = 31;
    ball_dx = -ball_dx;
  }
}

// Função para limpar a tela
  void clear_screen() {
    u8g.firstPage();
      do {
        u8g.drawBox(0, 0, 128, 64);
          } while (u8g.nextPage());
}

    /*-----------------------------------------------------------------------------------
   *                              JOGO PONG: FIM FUNÇÕES
   ------------------------------------------------------------------------------------*/

void setup() {
  // Se precisar girar o menu basta descomentar a linha abaixo
  //u8g.setRot180();
  
  IMH_Config();                    // Chama a rotina de Configuração das teclas juntamente com o Debounce
  menu_chamada_menu = 1;           // Força o inicio do menu no LCD
}

void loop() {  

if (menu_chamada_menu = 1 && tela == 0) {
    IMH_Debounce(); 
    u8g.firstPage();
    do  {
      DesenharMenu();
    } while(u8g.nextPage());
  }
  if(menu_chamada_menu = 1){
AtualizarMenu(); //update menu bar
  }

  /*-----------------------------------------------------------------------------------
   *                              PRIMEIRO ITEM DO MENU: 
   ------------------------------------------------------------------------------------*/
  if(menu_atualmente == 0 && digitalRead(IHM_Botao_Selecionar) == 0) // Verifica se o Item do menu está selecionado e se o botão SELECT foi precionado
  {
    tela = 1;                                    // Configura a tela
    menu_chamada_menu = 0;                       //Desabilita menu
  }
    if(tela==1) {                                // Verifica se está na tela
      u8g.firstPage();                           // Inicia a página da Tela
  do {  
   Tela1();                                      //Chama a subrotina da Tela
   if(digitalRead(IHM_Botao_VoltarMenu) == 0){   // Verifica se o botão BACK foi precionado
    menu_atualmente = 0;                         // Volta o cursor para a primeira posição do menu
    menu_chamada_menu = 1;                       // Habilita o Menu Principal
    tela = 0;                                    // Configura como a Primeira tela
  }
  } while(u8g.nextPage());                       // Finaliza a página da tela e vai à proxima tela
}
    /*-----------------------------------------------------------------------------------
   *                              SEGUNDO ITEM DO MENU: 
   ------------------------------------------------------------------------------------*/
  if(menu_atualmente == 1 && digitalRead(IHM_Botao_Selecionar) == 0) // Verifica se o Item do menu está selecionado e se o botão SELECT foi precionado
  {
    tela = 2;                                    // Configura a tela
    menu_chamada_menu = 0;                       //Desabilita menu
  }
    if(tela==2) {                                // Verifica se está na tela
      u8g.firstPage();                           // Inicia a página da Tela
  do {  
   Tela2();                                      //Chama a subrotina da Tela
   if(digitalRead(IHM_Botao_VoltarMenu) == 0){   // Verifica se o botão BACK foi precionado
    menu_atualmente = 0;                         // Volta o cursor para a primeira posição do menu
    menu_chamada_menu = 1;                       // Habilita o Menu Principal
    tela = 0;                                    // Configura como a Primeira tela
  }
  } while(u8g.nextPage());                       // Finaliza a página da tela e vai à proxima tela
  }
  /*-----------------------------------------------------------------------------------
   *                              TERCEIRO ITEM DO MENU: 
   ------------------------------------------------------------------------------------*/
  if(menu_atualmente == 2 && digitalRead(IHM_Botao_Selecionar) == 0) // Verifica se o Item do menu está selecionado e se o botão SELECT foi precionado
  {
    tela = 3;                                    // Configura a tela
    menu_chamada_menu = 0;                       //Desabilita menu
  }
    if(tela==3) {                                // Verifica se está na tela
      u8g.firstPage();                           // Inicia a página da Tela
  do {  
   Tela3();                                      //Chama a subrotina da Tela
   if(digitalRead(IHM_Botao_VoltarMenu) == 0){   // Verifica se o botão BACK foi precionado
    menu_atualmente = 0;                         // Volta o cursor para a primeira posição do menu
    menu_chamada_menu = 1;                       // Habilita o Menu Principal
    tela = 0;                                    // Configura como a Primeira tela
  }
  } while(u8g.nextPage());                       // Finaliza a página da tela e vai à proxima tela
  }
  /*-----------------------------------------------------------------------------------
   *                              QUARTO ITEM DO MENU: JOGO PONG
   ------------------------------------------------------------------------------------*/
  if(menu_atualmente == 3 && digitalRead(IHM_Botao_Selecionar) == 0) // Verifica se o Item do menu está selecionado e se o botão SELECT foi precionado
  {
    tela = 4;                                    // Configura a tela
    menu_chamada_menu = 0;                       //Desabilita menu
  }
    if(tela==4) {                                // Verifica se está na tela
      u8g.firstPage();                           // Inicia a página da Tela
  do {  
   Tela4();                                      //Chama a subrotina da Tela
   if(digitalRead(IHM_Botao_VoltarMenu) == 0){   // Verifica se o botão BACK foi precionado
    menu_atualmente = 0;                         // Volta o cursor para a primeira posição do menu
    menu_chamada_menu = 1;                       // Habilita o Menu Principal
    tela = 0;                                    // Configura como a Primeira tela
  }
  } while(u8g.nextPage());                       // Finaliza a página da tela e vai à proxima tela
  }
}
