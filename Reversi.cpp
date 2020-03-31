#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define SCREEN_HEIGHT 500 //設定遊戲視窗高度 
#define SCREEN_WIDTH 500 //設定遊戲視窗寬度
#define GRID_NUM 8 //設定遊戲方陣每邊格子數量 
#define LEFT_MARGINE 30 //設定左邊界 
#define TOP_MARGINE 45 //設定上邊界 
#define INIT_SPEED  80 //設定初始速度 
int PLAYONE_COLOR; //設定玩家一顏色
int PLAYTWO_COLOR; //設定玩家二顏色



//宣告棋子種類 
enum Chess {
	EMPTY, //空白 
	PLAY_ONE, //玩家一 
	PLAY_TWO //玩家二 
};

enum Mode {
	PLAYER, //玩家模式 
	AI_SINGLE, //玩家一, AI 玩家二 
	AI_BOTH //玩家一, 玩家二 都是AI 
};

//宣告棋子位子 
struct Location{
	int row; 
	int col;
};

//宣告紀錄落子位置的節點結構 
struct Node {
	Location loc; //棋盤位置 
	struct Node *next;	//指向下一個節點 
};

//定義指向節點結構的指標變數 
typedef struct Node *NodePointer;

void openWindow(); //開啟游戲視窗 
void Menu(); //遊戲主頁面 
void startgame(); //開始遊戲 
void ReversiRule(); //遊戲規則
void ReversiIntro(); //操作說明 
void Color(); //選擇顏色 
void Mode(); //選擇模式 
void closeGame(); //處理遊戲結束邏輯 
void playGame(int field[][GRID_NUM]); //遊戲進行邏輯 
void initChessboard(int field[][GRID_NUM]); //初始化棋盤狀態 
Location* getChessDown(int field[][GRID_NUM], Location *focusPtr); //取得玩家落子位置 
void setChess(int field[][GRID_NUM], Location chessLoc); //設定落子 
void drawChessboard(int field[][GRID_NUM]); //繪製遊戲區域 
void printBoardState(int field[][GRID_NUM]); //印出棋盤狀態 
bool checkValidation(NodePointer list, Location loc); //檢查該位置是否為合法的落子位置 
NodePointer getValidatedLocs(int field[][GRID_NUM]); //獲得所有合法下子的所有座標節點 
NodePointer addNode(NodePointer list, Location loc); //新增合法下子的座標資訊節點
int drawValidatedLocs(NodePointer list); //標記出所有該玩家所有合法的下棋位置 
void cleanValidatedLocs(NodePointer list); //清理標記 
void doReverse(int field[][GRID_NUM], Location chessLoc); //進行黑白棋翻轉 
int reverse(int field[][GRID_NUM], Location chessLoc, bool checkOnly);  //計算某下子座標所有可以翻轉的棋子數量， check_only = true 只進行計算，false 會進行棋子的翻轉 
void drawSquare(int row, int col, int color); //繪製色塊 
void drawFocus(int field[][GRID_NUM], Location focus); //繪製目標十字  
void cleanFocus(int field[][GRID_NUM], Location focus);//清除十字 
void drawCircle(int row, int col, int color); //繪製圓點 
void showGameWinMsg(); //遊戲結束訊息
void showInfo(); //顯示遊戲相關資訊 
void drawChess(int row, int col, int color);  //棋子 
Location* PLAYONE_AI(int field[][GRID_NUM], Location *focusPtr, NodePointer validated_locs);  //實作電腦控制邏輯 

char key; //操作按鍵 
int speed; //移動速度 
int currentPlayer = PLAY_ONE; //設定玩家 
int modeCount = 0; //控制模式紀錄 
int totalTime = 0; //紀錄遊戲時間 
int playMode = PLAYER; // 設定控制模式，玩家模式或AI模式 
int play1Score = 0; //玩家一分數 
int play2Score = 0; //玩家二分數 
int stepCount = 0; //回合計數器 


int main( )
{  	
	openWindow();
	
	while(TRUE){
		Menu();
	}
}

void startgame(){
		speed = INIT_SPEED;
		
		//設定遊戲場
	   	int field[GRID_NUM][GRID_NUM] = {0};

		playGame(field); //進行遊戲 
		if (key == 'q' || key == 'Q')
			closeGame(); //如果玩家輸入'q'離開遊戲
		else if (key == 's' || key == 'S')	
			Color();  //如果玩家輸入's' 繼續遊戲	
			  
}

//開啟游戲視窗
void openWindow(){
	initwindow(SCREEN_WIDTH + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3, "Backgammon");
}

void Menu(){    
    int j = 0;
    int choice1; 
    setcolor(WHITE);
    char mes0[30] = "======黑白棋======";
    char mes1[30] = "a.進入遊戲";
    char mes2[30] = "b.遊戲介紹";
    char mes3[30] = "c.操作說明";
    char mes4[30] = "q.離開遊戲";
    
    settextstyle(SMALL_FONT, HORIZ_DIR , 10);
 	outtextxy(SCREEN_WIDTH/7, SCREEN_HEIGHT / 2 -50, mes0);
 
 	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
 	outtextxy(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 30, mes1);
 
 	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
 	outtextxy(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 60, mes2);
 
	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
 	outtextxy(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 90, mes3);
 
	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
 	outtextxy(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 120, mes4);
    
    for(; ; j++){
		if(kbhit()) {
			choice1 = getch();
			if (choice1 == 'a' || choice1 == 'A') {     
				Color();
			}
			cleardevice();
			if(choice1 == 'b' || choice1 == 'B'){
				ReversiRule();
			}
			cleardevice();
			if(choice1 == 'c' || choice1 == 'C'){
				ReversiIntro();
			}
			cleardevice();
			if(choice1 == 'q' || choice1 == 'Q'){
				closeGame();
			}
			cleardevice();
		}
 	}
}

void Color(){
	cleardevice();
	int r = 0;
	int choice2 = 0;
	playMode = PLAYER;
	char mss1[40] = "======顏色選擇======";
	char mss2[40] = "a. 深灰色 x 白色";
	char mss3[80] = "b. 淺藍色 x 黃色";
	char mss4[40] = "c. 青色 x 淺粉色";
	char mss5[40] = "q. 回到主選單";

	settextstyle(SMALL_FONT, HORIZ_DIR , 10);
 	setcolor(15);
 	outtextxy(SCREEN_WIDTH/9, SCREEN_HEIGHT / 2 -50, mss1);
 
 	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
 	setcolor(8);
 	outtextxy(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 30, mss2);

 	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
 	setcolor(9);
 	outtextxy(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 60, mss3);
 
	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
	setcolor(13);
 	outtextxy(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 90, mss4);
 	
 	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
	setcolor(WHITE);
 	outtextxy(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 150, mss5);

	for(; ; r++){     
		if(kbhit()) {
			choice2 = getch();
			if (choice2 == 'a' || choice2 == 'A') {     
				PLAYONE_COLOR = 8;
				PLAYTWO_COLOR = 15;
				startgame();
			}
			cleardevice();
			if(choice2 == 'b' || choice2 == 'B'){
				PLAYONE_COLOR = 9;
				PLAYTWO_COLOR = 14;
				startgame();
			}
			cleardevice();
			if(choice2 == 'c' || choice2 == 'C'){
				PLAYONE_COLOR = 3;
				PLAYTWO_COLOR = 13;
				startgame();
			}
			cleardevice();
			if(choice2 == 'q' || choice2 == 'Q'){
				Menu();
				
			}
			cleardevice();
	
		}
 	}
}

void ReversiRule(){
 	int i = 0;
 	char msg1[40] = "======黑白棋規則說明======";
 	char msg2[40] = "遊戲開始後雙方輪流下子";
 	char msg3[80] = "若玩家在棋盤上沒有地方可以下子，則該玩家對手可以連下。";
 	char msg4[140] = "雙方都沒有棋子可以下時，棋局結束。";
 	char msg5[140] = "以棋子數目來計算勝負，棋子多的一方獲勝";
 	char msg6[140] = "按任意鍵即返回前頁面";
 	
	settextstyle(SMALL_FONT, HORIZ_DIR , 8);
   	outtextxy(SCREEN_WIDTH / 9, SCREEN_HEIGHT / 2 - 50, msg1);

   	settextstyle(SMALL_FONT, HORIZ_DIR , 6);
   	outtextxy(SCREEN_WIDTH / 3 + 10, SCREEN_HEIGHT / 2 + 30, msg2);

   	settextstyle(SMALL_FONT, HORIZ_DIR , 6);
   	outtextxy(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 + 50, msg3);

   	settextstyle(SMALL_FONT, HORIZ_DIR , 6);
   	outtextxy(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 70, msg4);

   	settextstyle(SMALL_FONT, HORIZ_DIR , 6);
   	outtextxy(SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT / 2 + 90, msg5);

   	settextstyle(SMALL_FONT, HORIZ_DIR , 6);
   	outtextxy(SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 + 150, msg6);
   	
    for(; ; i++){
     	if (getch()){
     		cleardevice();
	   		Menu();
		}  
		delay(100); 
 	}
}

void ReversiIntro(){
	int k = 0;
	char mssg1[40] = "======黑白棋操作說明======";
	char mssg2[40] = "↑:向上 1 格";
	char mssg3[80] = "←:向左 1 格";
	char mssg4[40] = "→:向右 1 格";
	char mssg5[40] = "↓:向下 1 格";
	char mssg6[40] = "空白鍵(Space):下子";
	char mssg7[40] = "按任意鍵即可返回前頁面";
	
	settextstyle(SMALL_FONT, HORIZ_DIR , 8);
   	outtextxy(SCREEN_WIDTH / 9, SCREEN_HEIGHT / 2 - 50, mssg1);

   	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
   	outtextxy(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 , mssg2);

   	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
   	outtextxy(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 + 30, mssg3);

   	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
   	outtextxy(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 + 60, mssg4);

   	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
   	outtextxy(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 90, mssg5);

   	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
   	outtextxy(SCREEN_WIDTH / 2 - 65, SCREEN_HEIGHT / 2 + 120, mssg6);
   	
   	settextstyle(SMALL_FONT, HORIZ_DIR , 7);
	outtextxy(SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 + 180, mssg7);
	
   	for(; ; k++){
		if (getch()){
			cleardevice();
	   		Menu();
		   }
		delay(1000000000); 
	}
}

//處理遊戲結束邏輯 
void closeGame(){
	exit(0);
}

//遊戲進行邏輯
void playGame(int field[][GRID_NUM]){
	
	drawChessboard(field); //繪製遊戲區域 
	
	NodePointer validated_locs = NULL;
	play1Score = 0, play2Score = 0;
	stepCount = 0;
	
	initChessboard(field); //初始化棋盤狀態 
   	printBoardState(field); //印出棋盤狀態，用於debug使用 
   	
   	validated_locs = getValidatedLocs(field); //計算所有合法座標  
   	drawValidatedLocs(validated_locs); //在棋盤上繪製這回合合法的座標 
	   	
	Location focus = {0, 0};
	Location* chessLocPtr;
	key = 0;
	int endPoint = 0;
	
	while(true){
		delay(speed); //決定每回合下棋速度 
		showInfo(); //顯示時間和分數資訊
		
		if(playMode == PLAYER){
			chessLocPtr = getChessDown(field, &focus);
		}else if(playMode == AI_SINGLE){
			if(currentPlayer == PLAY_ONE)
				chessLocPtr = getChessDown(field, &focus);
			else
				chessLocPtr = PLAYONE_AI(field, &focus, validated_locs);			
		}
		else { // playMode == AI_BOTH
			getChessDown(field, &focus);
			chessLocPtr = PLAYONE_AI(field, &focus, validated_locs);
		}
		
		if(chessLocPtr == NULL){
			//只有輸入大小寫的a, q 和 s，系統才有反應並將輸入結果拋到外層等待處理 
			if (key == 'q' || key == 'Q' || key == 's' || key == 'S')
				return;				
			else if (key == 'a' || key == 'A'){ 
				//決定是否改變模式 ，主要有玩家模式和電腦操控的AI模式 
				modeCount++;
				playMode = modeCount % 3; //?? 
				key = 0;
			}
			
			if (endPoint == 0)
				continue;
		}
		
		//玩家只能下在合法位置 
		if(chessLocPtr != NULL && checkValidation(validated_locs, *chessLocPtr) == false)
			continue;
		
		//連續兩回合都無法獲得合法座標，或者已經沒有可以下子的位置，遊戲結束 
		if(endPoint == 2 || (play1Score + play2Score) == GRID_NUM * GRID_NUM){ //判斷是否符合遊戲結束條件， 
			showGameWinMsg(); //顯示遊戲結束訊息，並等待玩家輸入選項
			return;
		}

		cleanValidatedLocs(validated_locs); //清理合法位置標記 
		if(chessLocPtr != NULL)
			setChess(field, *chessLocPtr); //如果玩家按下space，就在目標十字座標繪製棋子，並改變棋盤狀態 
 
 		//如果不是賽末點，進行吃子判斷，並翻轉棋子 
		if(endPoint == 0)
			doReverse(field, *chessLocPtr);
		
		if(currentPlayer == PLAY_ONE){
			currentPlayer = PLAY_TWO;
		}else{
			currentPlayer = PLAY_ONE;
		}
		
		printBoardState(field);
		
		// 取得下一回合的合法位置 
		validated_locs = getValidatedLocs(field);
		//如果該回合無法獲得合法的下子位置，賽末點+1 
		if(validated_locs == NULL)
			endPoint++;
		else{
			endPoint = 0;	
		}
		//繪製合法座標標記  
		int i=drawValidatedLocs(validated_locs);
		if (i==1) {
			endPoint=2;
			showGameWinMsg();
			return;
		}
		printf("end point: %d\n", endPoint);
							
	}		
}

// 初始化棋盤狀態 
void initChessboard(int field[][GRID_NUM]){
	Location loc;
   	currentPlayer = PLAY_ONE;
   	loc.row = GRID_NUM/2 - 1, loc.col = GRID_NUM/2 - 1;
   	setChess(field, loc);
   	
   	currentPlayer = PLAY_TWO;
   	loc.row = GRID_NUM/2, loc.col = GRID_NUM/2 - 1;
   	setChess(field, loc);
   	
   	currentPlayer = PLAY_ONE;
   	loc.row = GRID_NUM/2, loc.col = GRID_NUM/2;
   	setChess(field, loc);
   	
   	currentPlayer = PLAY_TWO;
   	loc.row = GRID_NUM/2 - 1, loc.col = GRID_NUM/2;
   	setChess(field, loc);
   	currentPlayer = PLAY_ONE;	
}

//繪製遊戲區域，依據遊戲場矩陣設定繪製物件 
void drawChessboard(int field[][GRID_NUM]){
   	int row = 0, col = 0;
   	int startX = 0, startY = 0, endX = 0, endY = 0;
   	cleardevice(); //清理螢幕畫面
   	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int squareWidth = SCREEN_WIDTH / GRID_NUM;
   	setlinestyle(SOLID_LINE, 0, 1); 
   	setcolor(WHITE);
	for(row = 0; row <= GRID_NUM; row ++){
		startX = LEFT_MARGINE + 0 * squareWidth + 0;
		startY =  TOP_MARGINE + row * squareHeight;
		endX = startX + GRID_NUM * squareWidth;
		line(startX, startY, endX, startY);
	}
	
	for(col = 0; col <=  GRID_NUM; col++){
		startX = LEFT_MARGINE + col * squareWidth;
		startY =  TOP_MARGINE + 0 * squareHeight + 0;
		endY = startY + GRID_NUM * squareHeight;
		line(startX, startY, startX, endY);
	}
}

//列印棋盤狀態 
void printBoardState(int field[][GRID_NUM]){
	int i,j;
	for(i=0;i<GRID_NUM;i++){
		for(j=0;j<GRID_NUM;j++)
			printf("%d ", field[i][j]);
		printf("\n");	
	}
}

//取得玩家落子位置
Location* getChessDown(int field[][GRID_NUM], Location *focusPtr){
		
	char keyPress;
	if(kbhit()) 
		keyPress = getch();
		
	if(keyPress == ' ' && field[focusPtr->row][focusPtr->col] == EMPTY){
		return focusPtr;
	}
		
	cleanFocus(field, *focusPtr);
	//decide focus moving direction	
	switch(keyPress){
		case KEY_RIGHT:
			if(focusPtr->col < GRID_NUM - 1)
				focusPtr->col = focusPtr->col + 1;
			break;			
		case KEY_LEFT:
			if(focusPtr->col > 0)
				focusPtr->col = focusPtr->col - 1;
			break;		
		case KEY_UP:
			if(focusPtr->row > 0)
				focusPtr->row = focusPtr->row - 1;
			break;				
		case KEY_DOWN:
			if(focusPtr->row < GRID_NUM - 1)
				focusPtr->row = focusPtr->row + 1;
			break;				
	}
	
	drawFocus(field, *focusPtr);
	//只有輸入大小寫的a, q 和 s，系統才有反應並將輸入結果拋到外層等待處理 
	if (keyPress == 'q' || keyPress == 'Q' || keyPress == 's' || keyPress == 'S' || keyPress == 'a' || keyPress == 'A'){
		key = keyPress;
	}
	return NULL;
}

//設定落子
void setChess(int field[][GRID_NUM], Location chessLoc){
	
	if(currentPlayer == PLAY_ONE){
		drawChess(chessLoc.row, chessLoc.col, PLAYONE_COLOR);
		play1Score++;
		if(field[chessLoc.row][chessLoc.col]==PLAY_TWO)
			play2Score--;
	}else{
		drawChess(chessLoc.row, chessLoc.col, PLAYTWO_COLOR);
		play2Score++;
		if(field[chessLoc.row][chessLoc.col]==PLAY_ONE)
			play1Score--;		
	}
	field[chessLoc.row][chessLoc.col] = currentPlayer;
	stepCount++;
}

//檢查該位置是否為合法的落子位置 
bool checkValidation(NodePointer list, Location loc){
	
	while(list != NULL){
		if(list->loc.row == loc.row && list->loc.col == loc.col)
			return true;
		list = list -> next;	
	}
	return false;
}

//獲得所有合法下子的所有座標節點 
NodePointer getValidatedLocs(int field[][GRID_NUM]){
	int row, col;
	NodePointer reversible_list = NULL;
	Location checkLoc;
	for(row=0; row < GRID_NUM; row++){
		for(col=0; col < GRID_NUM; col++){
			if(field[row][col] != EMPTY)
				continue;
			checkLoc.row = row, checkLoc.col = col;
			if(reverse(field, checkLoc, true) > 0){
				reversible_list = addNode(reversible_list, checkLoc);
			}		
		}
	}
	return reversible_list;
}

//新增合法下子的座標資訊節點
NodePointer addNode(NodePointer list, Location loc){
	NodePointer tail = NULL;
	NodePointer newNode = (NodePointer) malloc(sizeof(Node)); //初始化一個新節點 
	newNode -> loc = loc;
	newNode -> next = NULL;	
	if(list == NULL)
		return newNode;
	else{
		//尋找串列的尾巴 
		tail = list;
		while(tail -> next != NULL){
			tail = tail -> next;
		}
		tail -> next = newNode; //將尾巴節點連接到新節點 
		return list;
	}
}

//標記出所有該玩家所有合法的下棋位置 
int drawValidatedLocs(NodePointer list){
	
	if (list==NULL){
		printf("validated location do not exist!!\n");
		if(playMode == AI_BOTH) return 1;
		else if(playMode == AI_SINGLE) return 1;
		else return 0;
	}

	printf("validated location: ");
	while(list != NULL){
		printf("(%d, %d) ",  list -> loc.row, list -> loc.col);
		
		if(currentPlayer == PLAY_ONE)
			drawCircle(list -> loc.row, list -> loc.col, PLAYONE_COLOR);
		else
			drawCircle(list -> loc.row, list -> loc.col, PLAYTWO_COLOR);
		
		list = list -> next;
	}
	printf("\n");
	return 0;
}

//清理標記 
void cleanValidatedLocs(NodePointer list){

	while(list != NULL){
		drawCircle(list -> loc.row, list -> loc.col, BLACK);
		list = list -> next;
	}
	printf("\n");

}

//進行黑白棋翻轉 
void doReverse(int field[][GRID_NUM], Location chessLoc){
	reverse(field, chessLoc, false);
}

//計算某下子座標所有可以翻轉的棋子數量， check_only = true 只進行計算，false 會進行棋子的翻轉 
int reverse(int field[][GRID_NUM], Location chessLoc, bool checkOnly){
	int dirSize = 8;
	int rowDir[] = {-1, -1, -1,  0, 0,  1, 1, 1};
	int colDir[] = {-1,  0,  1, -1, 1, -1, 0, 1};
	int i, rowNext, colNext;
	int totalReversed = 0;
	Location loc;
	
	for(i = 0; i<dirSize; i++){
		rowNext = chessLoc.row;
		colNext = chessLoc.col;
		int reverseCount = 0, count = 0;
		while(true){
			rowNext += rowDir[i];
			colNext += colDir[i];		
			if(field[rowNext][colNext] == EMPTY || rowNext < 0 || colNext < 0 || rowNext > GRID_NUM-1 || colNext > GRID_NUM-1){
				break;
			} else if(field[rowNext][colNext] != currentPlayer){
				count++;
			} else if(field[rowNext][colNext] == currentPlayer){
				reverseCount = count;
				break;
			}	
		}
		
		if(reverseCount > 0 && checkOnly == false){
			int j;
			rowNext = chessLoc.row;
			colNext = chessLoc.col;
			for(j = 0; j < reverseCount; j++){
				rowNext += rowDir[i];
				colNext += colDir[i];
				loc.row = rowNext;
				loc.col = colNext;
				setChess(field, loc);
			}
		}
		
		totalReversed += reverseCount; 
	}
	return totalReversed;
}

//繪製目標十字
void drawFocus(int field[][GRID_NUM], Location focus){
	int focusX = 0, focusY = 0;
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int squareWidth = SCREEN_WIDTH / GRID_NUM;
   	focusX = LEFT_MARGINE + focus.col * squareWidth + squareWidth / 2;
   	focusY =  TOP_MARGINE + focus.row * squareHeight + squareHeight / 2;
   	setlinestyle(SOLID_LINE, 0, 1); 
   	setcolor(YELLOW);
   	line(focusX -5, focusY, focusX + 5, focusY);
   	line(focusX, focusY - 5, focusX, focusY + 5);
}

//清除目標十字
void cleanFocus(int field[][GRID_NUM], Location focus){
	if(field[focus.row][focus.col] == PLAY_ONE)
		setcolor(PLAYONE_COLOR);
	else if(field[focus.row][focus.col] == PLAY_TWO)
		setcolor(PLAYTWO_COLOR);	
	else
		setcolor(BLACK);
			
	int focusX = 0, focusY = 0;
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int squareWidth = SCREEN_WIDTH / GRID_NUM;
   	focusX = LEFT_MARGINE + focus.col * squareWidth + squareWidth / 2;
   	focusY =  TOP_MARGINE + focus.row * squareHeight + squareHeight / 2;
   	setlinestyle(SOLID_LINE, 0, 1); 
   	
   	line(focusX -5, focusY, focusX + 5, focusY);
   	line(focusX, focusY - 5, focusX, focusY + 5);
}

//繪製方塊
void drawSquare(int row, int col, int color){
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int SquareWidth = SCREEN_WIDTH / GRID_NUM;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + 1;
   	top =  TOP_MARGINE + row * squareHeight + 1;
	right = left + SquareWidth - 1;
   	bottom = top + squareHeight - 1;
   	 
	setfillstyle(SOLID_FILL, color); //設定繪製物件的為實心和顏色 
   	bar(left , top, right, bottom);	//設定繪製方塊的位置 
}

//繪製棋子
void drawChess(int row, int col, int color) {
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
    int SquareWidth = SCREEN_WIDTH / GRID_NUM;
 	int left = 0, right = 0, bottom = 0, top = 0;
 	left = LEFT_MARGINE + col * SquareWidth + 3;
    top =  TOP_MARGINE + row * squareHeight + 3;
 	right = left + SquareWidth - 3;
 	bottom = top + squareHeight - 3;
 	int lr_center = (left + right)/2;
 	int td_center = (top + bottom)/2;

 	int r = 27;    
    setcolor(color);
 	setfillstyle(SLASH_FILL,color); //設定繪製物件的為實心和顏色 
 	circle(lr_center,td_center,r);
 	floodfill(lr_center,td_center,color);
}

//繪製圓點 
void drawCircle(int row, int col, int color){
	int squareHeight = SCREEN_HEIGHT / GRID_NUM;
   	int SquareWidth = SCREEN_WIDTH / GRID_NUM;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + 3;
   	top =  TOP_MARGINE + row * squareHeight + 3;
	right = left + SquareWidth - 3;
	bottom = top + squareHeight - 3;
	int lr_center = (left + right)/2;
	int td_center = (top + bottom)/2;

	int r = 10;   	
   	setcolor(color);
//	setfillstyle(SOLID_FILL,color); //設定繪製物件的為實心和顏色 
	circle(lr_center,td_center,r);
}

//遊戲結束訊息
void showGameWinMsg(){
   	//cleardevice(); //清理所有螢幕資料，如果希望只顯示訊息時，取消註解 
	int i = 0;
	char msg1[20] = "";
	if(play1Score == play2Score){
		strcat(msg1, "End In A Draw!!");
	}else if(play1Score > play2Score){
		strcat(msg1, "Player One Win!!");
	}else
		strcat(msg1, "Player Two Win!!");
			
	char msg2[40] = "press [q] to quit or [s] to restart!!";
   	for(; ; i++){
	   	setcolor(i%14);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg1);
	   	
	   	setcolor(WHITE);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	   	outtextxy(20, SCREEN_HEIGHT / 2 + 50, msg2);
	   	
	   	delay(200);
	   	
	   	setcolor(BLACK);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 5);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg1);	   
		   	
	   	if(kbhit()) {
			key = getch();	
			if (key == 'q' || key == 'Q' || key == 's' || key == 'S') {
				return; 				
			}
		}
	}	
}

//顯示遊戲相關資訊
void showInfo(){
	totalTime += speed;
	char timeMsg[45] = " Time:";
	char modeMsg[20] = "";
	char optMsg1[50] = "press [q] to quit, [s] to restart or";
	char optMsg2[50] = "press [a] to change mode.";
	char optMsg3[50] = "press [space] to set chess.";
	char play1RoundMsg[20] = "PLAYER ONE ROUND";
	char play2RoundMsg[20] = "PLAYER TWO ROUND";	
	char stepCountMsg[10] = "STEP:";
	
	char time[10];
	char step[10];
	char score1Msg[10];
	char score2Msg[10];
	int left, top;
	sprintf(time, "%5d", totalTime/1000);
	strcat(timeMsg, time);
	strcat(timeMsg, " sec.");
	
	sprintf(score1Msg, "%3d", play1Score);
	sprintf(score2Msg, "%3d", play2Score);
	sprintf(step, "%3d", stepCount);
	strcat(stepCountMsg, step);
	
	setcolor(WHITE); //設定文字顏色 
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1); //設定字型，水平或垂直和字型大小 
   	outtextxy(0, 0, timeMsg); //依據坐標輸出文字到螢幕
   	
   	if(currentPlayer == PLAY_ONE){
   		outtextxy(30, 20, play1RoundMsg);
		setfillstyle(SOLID_FILL,PLAYONE_COLOR);  	  
	}else{
		outtextxy(30, 20, play2RoundMsg); 
		setfillstyle(SOLID_FILL,PLAYTWO_COLOR);  
	}
	
	left = 5, top = 20;
   	bar(left , top, left + 20, top + 20);		
	   		
   	if(playMode == PLAYER){
   		strcat(modeMsg, "Player Mode      ");
   				
	}else if(playMode == AI_SINGLE){
   		strcat(modeMsg, "P1 player, P2 AI");    		
	}else
		strcat(modeMsg, "P1, P2 AI both   ");

   	setcolor(LIGHTMAGENTA);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(SCREEN_WIDTH - LEFT_MARGINE * 4, 0, modeMsg);
	
	setcolor(WHITE); //設定文字顏色
	left = LEFT_MARGINE * 2 + GRID_NUM * SCREEN_WIDTH / GRID_NUM / 3;
	top = 20;	      	
	outtextxy(left + 25, 20, stepCountMsg);	
	
	left = LEFT_MARGINE * 4 + GRID_NUM * SCREEN_WIDTH / GRID_NUM / 2;
	top = 20;
	setfillstyle(SOLID_FILL,PLAYONE_COLOR);
	bar(left , top, left + 20, top + 20);	      	
	outtextxy(left + 25, 20, score1Msg);
	
	left = LEFT_MARGINE * 4 + GRID_NUM * SCREEN_WIDTH / GRID_NUM / 2 + 100;
	setfillstyle(SOLID_FILL,PLAYTWO_COLOR);
	bar(left, top, left + 20, top + 20);	      	
	outtextxy(left + 25, 20, score2Msg);
   	
   	setcolor(LIGHTGREEN);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(0, TOP_MARGINE + (GRID_NUM) * SCREEN_HEIGHT / GRID_NUM, optMsg1);
	outtextxy(0, TOP_MARGINE + (GRID_NUM) * SCREEN_HEIGHT / GRID_NUM + 20, optMsg2);	      	
	outtextxy(0, TOP_MARGINE + (GRID_NUM) * SCREEN_HEIGHT / GRID_NUM + 40, optMsg3);
}

//電腦玩家，請在此function實作AI功能 
Location* PLAYONE_AI(int field[][GRID_NUM],  Location *focusPtr, NodePointer validated_locs){
	// MAX_loc: 會翻最多棋子的location 
	// current_loc: 目前location 
	Location MAX_loc,current_loc;
	int max_num=0, row, col;
	// 看field中每個點，把每個點的location用reverse算會翻轉的棋子的個數 
	// 如果reverse return的值 > max_num 就把current_loc存到 MAX_loc 中，並把 max_num存成 MAX_loc 的 reverse 值 
	for(row=0; row < GRID_NUM; row++){
		for(col=0; col < GRID_NUM; col++){
			if(field[row][col] != EMPTY)
				continue;
			current_loc.col=col;
			current_loc.row=row;
			printf("max location: [%d][%d]\tmax num: %d\n", current_loc.row, current_loc.col, max_num);
			if(reverse(field, current_loc, true) > max_num){
				MAX_loc.col=current_loc.col;
				MAX_loc.row=current_loc.row;
				max_num = reverse(field, current_loc, true);
			}		
		}
	}
	printf("\nmax location: [%d][%d]\nmax num: %d\n", MAX_loc.row, MAX_loc.col, max_num);
	focusPtr->row = MAX_loc.row;
	focusPtr->col = MAX_loc.col;
	return focusPtr;
}
