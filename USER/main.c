#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "time.h"
#include "pcf8574.h"


/************************************************
��Ŀ���ƣ�����STM32��̰���ߴ���ս
����������Keli5 + ����ԭ��STM32F767
��		�ߣ�����ѧԺ2022���ƿư� ����
************************************************/

//������ɫ����
u32 color1  = WHITE;
u32 color2  = BLACK;
u32 color3  = BLUE;
u32 color4  = BRED;
u32 color5  = GRED;
u32 color6  = GBLUE;
u32 color7  = RED;
u32 color8  = MAGENTA;
u32 color9  = GREEN;
u32 color10 = CYAN;
u32 color11 = YELLOW;
u32 color12 = BROWN; //��ɫ
u32 color13 = BRRED; //�غ�ɫ
u32 color14 = GRAY; //��ɫ

//GUI��ɫ����
u32 color15 = DARKBLUE;	//����ɫ
u32 color16 = LIGHTBLUE;	//ǳ��ɫ  
u32 color17 = GRAYBLUE; //����ɫ
//������ɫΪPANEL����ɫ 
u32 color18 = LIGHTGREEN; //ǳ��ɫ
//	u32 color19 = LIGHTGRAY; //ǳ��ɫ(PANNEL)
u32 color20 = LGRAY; //ǳ��ɫ(PANNEL),���屳��ɫ
u32 color21 = LGRAYBLUE; //ǳ����ɫ(�м����ɫ)
u32 color22 = LBBLUE; //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

#define MAX_LENGTH 50 //���ֵ
#define true 1
#define false 0
#define pix_width 4
#define UP 3
#define RIGHT 0
#define LEFT 2
#define DOWN 1
int game_over_flag=false;
u32 score=0;
u8 key;
int food_x=160;                                                                                                                                                                                                                                                                                                                          
int food_y=160;

struct
{
	int snake_grid[MAX_LENGTH][2];
	int lenth;
	int direction;
}snake;
//��ʼ��̰����
void init_snake()
{	
	int i;
	snake.lenth=3;
	snake.direction=RIGHT;
	score=0;
	snake.snake_grid[0][0]=48;
	snake.snake_grid[0][1]=48;
	for(i=1;i<snake.lenth;i++)
	{                                                                                                                                                                                                                                                                                        
		snake.snake_grid[i][0]=snake.snake_grid[0][0]-i*(pix_width);
		snake.snake_grid[i][1]=snake.snake_grid[0][1];
		
	}
}
//������ײ�ж�
int is_hit_body() {
    int i;
    int x = snake.snake_grid[0][0];
    int y = snake.snake_grid[0][1];
    for (i = 1; i < snake.lenth; i++) {
        if (snake.snake_grid[i][0] == x && snake.snake_grid[i][1] == y) {
            return true;
        }
				if(snake.snake_grid[i][0]==0) 
				{
					break;
				}
    }
    return false;
}

//�߽����ײ�ж�
int is_hit_boundary() {
    int x = snake.snake_grid[0][0];
    int y = snake.snake_grid[0][1];
    if (x < 24 || x > 454) {
        return true;
    } 
		else if( y < 24 || y > 590){
			return true;
		}
		else {
        return false;
    }
}
//���ֻ��ƺ���
//���Ƶ�ͼ
void paint_map()
{
	int x;
	for(x=0;x<pix_width;x++)
	LCD_DrawRectangle(10+x,10+x,464+x,600+x);
}
//����̰����ͷ��
void paint_head(int x,int y)
{	
	int pix = pix_width;
	LTDC_Fill(x-pix,y-pix,x+pix,y+pix,color13);
}
//����̰��������
void paint_body(int x,int y)
{
	int pix=pix_width;
	LTDC_Fill(x-pix,y-pix,x+pix,y+pix,color12);
}
//����ʳ��
void paint_food( )
{
	LTDC_Fill(food_x-pix_width,food_y-pix_width,food_x+pix_width,food_y+pix_width,color7);
}
//ȡ�����
int getRandon()
{       
    int min = 24;
    int max = 400;

    int range = (max - min) / 8; // ??????8???
    int r = (rand() % range) * 8 + min; // ??8???
    return r;
}
//����λ��
void update_position(){
	int i;
	for(i=snake.lenth-1;i>0;i--)
		{
			snake.snake_grid[i][0]=snake.snake_grid[i-1][0];
			snake.snake_grid[i][1]=snake.snake_grid[i-1][1];
		}
}
//ˢ��ʳ��
void update_food()
{
	int x,y;
	x=getRandon();
	y=getRandon();
	food_x=x;
	food_y=y;
}
//��ʳ��
int is_ated_food()
{	
	int x,y;
	x=snake.snake_grid[0][0];
	y=snake.snake_grid[0][1];
	if(x==food_x && y==food_y){
		return true;
	}
	return false;	
}
//�ƶ�
void move()
{
	int ea=false;
	int dr=snake.direction;
	int hit_b=is_hit_boundary();
	int hit_itself=is_hit_body();
	ea=is_ated_food();
	if(ea){
		PCF8574_WriteBit(BEEP_IO,0);	//���Ʒ�����
		delay_ms(200);
		PCF8574_WriteBit(BEEP_IO,1);	//���Ʒ�����
		++snake.lenth;
		score+=10;
		update_food();
	}

	switch(dr)
	{
		case RIGHT:
			update_position();
			snake.snake_grid[0][0]=snake.snake_grid[0][0]+2*pix_width;
			if(hit_b || hit_itself)
				game_over_flag=true;		
		break;
		case DOWN:
			update_position();
			snake.snake_grid[0][1]=snake.snake_grid[0][1]+2*pix_width;
			if(hit_b  || hit_itself)
				game_over_flag=true;
			break;
		case LEFT:
			update_position();
			snake.snake_grid[0][0]=snake.snake_grid[0][0]-2*pix_width;
			if(hit_b || hit_itself)
				game_over_flag=true;
			break;
		case UP:
			update_position();
			snake.snake_grid[0][1]=snake.snake_grid[0][1]-2*pix_width;
			if(hit_b || hit_itself)
				game_over_flag=true;
		break ;
	}
	
}
//�ı����
void paint_menu()
{
	
	char l[10];
	char s[10];
	sprintf(l, "%d", snake.lenth);
	sprintf(s, "%d", score);
	LCD_ShowString(30,700,50,16,16,"Lenth:");
	LCD_ShowString(80,700,50,16,16,l);
	LCD_ShowString(30,740,50,16,16,"Score:");
	LCD_ShowString(80,740,50,16,16,s);
}

//ˢ����Ļ
void refresh(int grid[][2])
{	
	int i;
	LTDC_Fill(20,20,454,590,color1);
	//LTDC_Clear(color1);
	paint_map();
	paint_head(grid[0][0],grid[0][1]);
	for(i=1;i<snake.lenth;i++)
	{
		paint_body(grid[i][0],grid[i][1]);
	}
	paint_food();
	paint_menu();
}
//��ȡ����ֵ
void detected_key()
{
				key=KEY_Scan(1);
			switch(key)
			{
				case KEY0_PRES:
					if(snake.direction!=LEFT)
						snake.direction=RIGHT;
					break;
				case KEY1_PRES:
					if(snake.direction!=UP)
						snake.direction=DOWN;
					break;
				case KEY2_PRES:
					if(snake.direction!=RIGHT)
						snake.direction=LEFT;
					break;
				case WKUP_PRES:
					if(snake.direction!=DOWN)
					snake.direction=UP;
					break;
			}
}
//ʤ������
void victory(){
while(1){
			LCD_Clear(WHITE);
			key=KEY_Scan(1);
			LCD_ShowString(60,200,200,16,16,"Successed!");
			LCD_ShowString(100,250,200,16,16,"Press reset key to restart");
			PCF8574_WriteBit(BEEP_IO,0);	//���Ʒ�����
			delay_ms(200);
		}
}
int main(void)
{
    Stm32_Clock_Init(360,25,2,8);   
    delay_init(180);                
    uart_init(115200);              //
    LED_Init();                     // 
    KEY_Init();                     //
    SDRAM_Init();                   //
    LCD_Init();                     //LCD
		init_snake();
		srand(20102);
		PCF8574_Init();
	
		while(1){
			LCD_Clear(WHITE);
			key=KEY_Scan(1);
			LCD_ShowString(30,200,200,16,16,"Press any key to start");
			if(key){
				PCF8574_WriteBit(BEEP_IO,0);	//���Ʒ�����
				delay_ms(200);
				PCF8574_WriteBit(BEEP_IO,1);	//���Ʒ�����
				break;
			}
			delay_ms(200);
		}
		while(game_over_flag==false)
		{	
			detected_key();
			refresh(snake.snake_grid);
			delay_ms(200);
			detected_key();
			move();
			if(snake.lenth>=MAX_LENGTH)
			{
				victory();
			}
		}
		while(1){
			LCD_Clear(WHITE);
			key=KEY_Scan(1);
			LCD_ShowString(60,200,200,16,16,"Game over!");
			PCF8574_WriteBit(BEEP_IO,0);	//���Ʒ�����
			delay_ms(200);
		}
		
}
