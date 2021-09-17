//Проект : Шах 
// от : Илиян Костов
// Ф. н : 19621609
// Специалност: СИТ
// Група : 4
// Курс : 2



#include<iostream>
#include<stdio.h>
#include<string>
#include<typeinfo>
#include<exception>
#include<fstream>
#include<locale>
using namespace std;

const string file_name_taken = "Taken_figures.txt";
	const string file_name_board= "Board_figures.txt";
	static string temp="";
	static string temp_board="";
	static bool flag=false;
	static bool flag_board=false;
class Figure{
	char Color;

	
public:
	
	Figure(){}
	Figure(char argColor) : Color(argColor){}

	virtual const char getIcon()=0;
	const char GetColor(){return Color;}
		virtual bool move(int curr_row,int curr_col,int dest_row,int dest_col) =0;
	



};



static Figure* board[8][8];

class Pawn: public Figure {

	bool flag;
	const char getIcon() { return '1'; }

public:

	Pawn(char argColor) : Figure(argColor){flag=true;}

	bool move(int curr_row,int curr_col,int dest_row,int dest_col) {
	
		int moves=1;
		if (flag) moves=2;
		if (board[dest_row][dest_col] == 0 || board[dest_row][dest_col]->GetColor() != board[curr_row][curr_col]->GetColor() ) {

	

				switch(GetColor()) {
bool flag3;
				case 'W':
					
					flag3=(dest_row==curr_row+1 &&  (dest_col==curr_col-1 || dest_col==curr_col+1) );

					if (board[dest_row][dest_col] != 0) {
						
							if ( flag3 && board[dest_row][dest_col]->GetColor() != GetColor()) return true; 
					}


					else if (board[dest_row][dest_col]==0) {
					if ((dest_row==curr_row+1 || dest_row==curr_row +moves ) && dest_col==curr_col) { flag=false;return true; }
					}
					break;

				case 'B':
						flag3=(dest_row==curr_row-1 &&  (dest_col==curr_col-1 || dest_col==curr_col+1) );

						if (board[dest_row][dest_col]!=0) {
							if ( flag3 && board[dest_row][dest_col]->GetColor() != GetColor()) return true; 
						}

						else if (board[dest_row][dest_col]==0) {
								if ((dest_row==curr_row-1 || dest_row==curr_row-moves)&& dest_col==curr_col) {flag=false;return true;}
						}
						
					
						
					
					
					break;
			
				}


			
		
		
	}
			return false;

	}

};

class Rook : virtual public Figure { 

	const char getIcon() { return 'R';}

public :

	Rook(){}
	Rook(char argColor) : Figure(argColor){}

	bool move(int curr_row,int curr_col,int dest_row,int dest_col) {
		
		if (board[dest_row][dest_col] == 0  || board[dest_row][dest_col]->GetColor() != GetColor()) {

			if ( (dest_row==curr_row+1 || dest_col==curr_col+1) || (dest_row==curr_row-1 || dest_col==curr_col-1) && board[dest_row][dest_col]->GetColor() !=GetColor()) return true;

			if (curr_row==dest_row) { // ако ще мърда вертикално 

				int dx=curr_col<dest_col ? 1: -1; 
				for(int j=curr_col+dx;j!=dest_col;j+=dx) {
					if (board[curr_row][j]!=0 ) return false;
				
				}

				

		}////////rows

			else if (curr_col== dest_col)  {

				int dy=curr_row<dest_row ? 1:-1;
				for(int j=curr_row+dy;j!=dest_row;j+=dy) {
					if (board[j][curr_col]!=0) return false;
				}
		
		}///////cols
			if (curr_row != dest_row && curr_col != dest_col) return false; 
		return true;	
		}
	

		else return false;
	
	}


};





class Knight : public Figure {

	const char getIcon() { return 'H';}

public :

	Knight(char argColor) : Figure(argColor){}

	bool move(int curr_row,int curr_col,int dest_row,int dest_col) {
		//ако позицията е празна или позията е заета от противник да 
		if (board[dest_row][dest_col] == 0  || board[dest_row][dest_col]->GetColor() != GetColor()) {

			if (dest_row== curr_row+1 || dest_row==curr_row-1) {

				if (dest_col==curr_col+2 || dest_col==curr_col-2) return true;

			}

			else if (dest_row == curr_row+2 || dest_row==curr_row-2) {

				if (dest_col==curr_col+1 || dest_col==curr_col-1) return true;

		}
		}
			return false;
	}


};


class Bishop : virtual public Figure {

	const char getIcon() { return 'B';}

public :
	Bishop(){}
	Bishop(char argColor) : Figure(argColor){}

	bool move(int curr_row,int curr_col,int dest_row,int dest_col) {

		if (dest_col - curr_col == dest_row - curr_row || dest_col - curr_col == curr_row - dest_row ) {

			int moved_Row = dest_row - curr_row > 0 ? 1: -1;
			int moved_Col = dest_col - curr_col > 0 ? 1: -1;

			int i,j;

			for(i=curr_row+moved_Row,j=curr_col+moved_Col;i!=dest_row,j!=dest_col;i+=moved_Row,j+=moved_Col) {
				if ( board[i][j]!=0  ) { return false;}
			}
			if (board[dest_row][dest_col]!=0) {if (board[dest_row][dest_col]->GetColor()!=GetColor()) return true;
			else return false;
			}
			return true;
			

			
		}
		return false;
			
			
			}
	

		

};



class Queen : public  Rook ,public Bishop {

	const char getIcon() { return 'Q';}

public :

	Queen(char argColor) : Rook::Figure(argColor)  {}

	bool move(int curr_row,int curr_col,int dest_row,int dest_col) {

		if (Rook::move(curr_row,curr_col,dest_row,dest_col) || Bishop::move(curr_row,curr_col,dest_row,dest_col))
			return true;

		return false;


	}


};


class King : public Figure {

	const char getIcon() { return 'K';}

public :

	King(char argColor) : Figure(argColor){}

	bool move(int curr_row,int curr_col,int dest_row,int dest_col) {

		bool check_row = dest_row - curr_row >=-1 && dest_row - curr_row <= 1;
		bool check_col= dest_col - curr_col >= -1 && dest_col - curr_col <= 1;

		if ( check_row && check_col && board[dest_row][dest_col]!=0 ) { if (board[dest_row][dest_col]->GetColor() !=GetColor()) return true;}
		else if  (check_row && check_col && board[dest_row][dest_col]==0 ) return true;
		return false;


	}

};







class Board  {

	

public:

	static void WriteFileStats_taken(int x,int y) {

		
	
		ofstream ofile;
		ofile.open(file_name_taken,ios::binary | ios::out | ios::app);
		

		if (!ofile.is_open()) cout<<"\nCan't open file!\n";
		else {
		ofile<<temp;
		ofile<<"\n";
		}

		ofile.close();
		
	}

	static void printStats_taken() {

		ifstream ifile;
		ifile.open(file_name_taken,ios::binary | ios::in);

		if (!ifile.is_open()) cout<<"\nCan't open file!\n";
		else {
		for(string i ;getline(ifile,i);) {
			cout<<i<<endl;
		}
		}
		ifile.close();

	}


	static void printStats_board(); 
	
	Board() {}


	
		

	
};





class Game {

	char Player_Turn;

public:

	Game() {


		//Syzdavane na dyska
		for(int i=0;i<8;i++) {

			for(int j=0;j<8;j++) {

				board[i][j]=0;
				//първо всичко с нули
			}
		}

		//Cherni Figuri Black
			for(int j=0;j<8;j++) {
				board[6][j]=new Pawn('B');
			}
				board[7][0] = new Rook('B');
				board[7][1] = new Knight('B');
				board[7][2] = new Bishop('B');
				board[7][3] = new King('B');
				board[7][4] = new Queen('B');
				board[7][5] = new Bishop('B');
				board[7][6] = new Knight('B');
				board[7][7] = new Rook('B');


				


				//Beli Figuri White
			for(int j=0;j<8;j++) {
				board[1][j]=new Pawn('W');
			}
				board[0][0] = new Rook('W');
				board[0][1] = new Knight('W');
				board[0][2] = new Bishop('W');
				board[0][3] = new King('W');

			
				board[0][4] = new Queen('W');
				board[0][5] = new Bishop('W');
				board[0][6] = new Knight('W');
				board[0][7] = new Rook('W');

	}

	void print() {

		const int kiSquareWidth = 4;
		const int kiSquareHeight = 3;
		for (int i = 0; i < 8*3; ++i) {
			int Sq_Row = i/3 ;
			
			if (i % 3 == 1) {
				cout << '-' << (char)('0' + 7 - Sq_Row) << '-';
			} else {
				cout << "---";
			}
			
			for (int j = 0; j < 8*4; ++j) {
				int Sq_Col = j/4;
				if (((i % 3) == 1) && ((j % 4) == 1 || (j % 4) == 2) && board[7-Sq_Row][Sq_Col] != 0) {
					if ((j % 4) == 1) {
						cout << board[7-Sq_Row][Sq_Col]->GetColor();
					} else {
						cout << board[7-Sq_Row][Sq_Col]->getIcon();
					}
				} else {
					if ((Sq_Row + Sq_Col) % 2 == 1) {
						cout << '|';
					} else {
						cout << ' ';
					}
				}
			}
			cout << endl;
		}
		
		for (int i = 0; i < 3; ++i) {
			if (i % 3 == 1) {
				cout << "---";
				for (int j = 0; j < 8*4; ++j) {
					int Sq_Col = j/4;
					if ((j % 4) == 1) {
						cout << (Sq_Col + 0);
					} else {
						cout << '-';
					}
				}
				cout << endl;
			} else {
				for (int k = 1; k < 9*4; ++k) {
					cout << '-';
				}
				cout << endl;
			}
		}
	}


	
	static void stats(int x,int y) {

		if (board[x][y] !=0) {
		Figure* getFigure=board[x][y];
		string Name,Type="White";
		switch(getFigure->getIcon()) {

		case '1' : Name="Pawn";
			break;

		case 'R': Name="Rook";
			break;

		case 'H': Name="Knight";
			break;

		case 'B': Name="Bishop";
			break;

		case 'Q': Name="Queen";
			break;

		case 'K': Name="King";
			break;

		}
		
		if (getFigure->GetColor() =='B') Type="Black";
		

		if (flag) {temp="Figure :"+Name+"\nType: "+Type+"\n";flag=false;}


		cout<<"Figure :"<<Name<<"\nType: "<<Type+"\n"<<"Position x: "<<x<<"\nPosition y: "<<y<<"\n";
		}

		else {cout<<"There is no figure in position: "<<x<<" , "<<y<<endl;}

	}
	
	bool Game_move(int curr_x,int curr_y,int dest_x,int dest_y) {

		if (board[curr_x][curr_y]!=0) {
		
		if (board[curr_x][curr_y]->move(curr_x,curr_y,dest_x,dest_y)) {

			
			
			char choice;
			cout<<"\nCorrect movement!\n\n\nUndo ?\n(Y/N): ";
				cin>>choice;
			
		
			if (choice == 'Y' || choice=='y') return false; 
			else {
			if (board[dest_x][dest_y]!=0) {flag=true;cout<<"Taken figure:\n\n"; stats(dest_x,dest_y);Board::WriteFileStats_taken(dest_x,dest_y);}
			board[dest_x][dest_y]=board[curr_x][curr_y];
			board[curr_x][curr_y]=NULL;
			
			return true;}
		}
		else{ cout<<"\nCannot make that move!"<<endl;
		return false;}
		}
		else {cout<<"\nThere is no figure in position: "<<curr_x<<" ,"<<curr_y<<endl;return false;}
		

	}


	void Start_game(){
		Player_Turn='W';
		int x,y;
		int x2,y2;
		int choice;
		string strtemp;
		do {
			system("cls");
			print();

			
			if (Player_Turn == 'W') strtemp="White";
			else strtemp="Black";
			
		
				cout<<"\n\n"<<strtemp<<" player's turn: ";

				cout<<"\n\n1.Move\n2.Stats\n3.Taken figures\n4.Figures on board\n\nSelect: ";
				cin>>choice;
				switch (choice) {

				case 1:
				cout<<"\nChoose position: ";
				cout<<"\npos x: ";
				cin>>x;
				cout<<"\npos y: ";
				cin>>y;
				cout<<"\n\nMove to position:pos x: ";

				cin>>x2;
				cout<<"\npos y: ";
				cin>>y2;
				 if (board[x][y] != 0 ) {
				if (board[x][y]->GetColor() == Player_Turn) {

					if (Game_move(x,y,x2,y2)) { 
						if (Player_Turn=='W') Player_Turn='B';
						else Player_Turn='W';
					}
					system("pause");
				


				}else {cout<<"\nInvalid figure!\n";system("pause");}
				 }else {cout<<"\nThere is no figure in position: "<<x<<","<<y<<endl;system("pause");}
				break;

				case 2:
					cout<<"\nChoose position: ";
				cout<<"\npos x: ";
				cin>>x;
				cout<<"\npos y: ";
				cin>>y;

				 stats(x,y);
				 system("pause");
					break;

				case 3:
					if (temp!="")
					Board::printStats_taken();
					else cout<<"\nThere are no taken figures!\n";
					system("pause");
					break;

				case 4:
					
						Board::printStats_board();
						system("pause");
					break;
				default:
					cout<<"\nInvalid choice!";
					system("pause");
					break;
				}

		}while(GameOver());
	}


	bool GameOver(){

		for(int i=0;i<8;i++) {

			for(int j=0;j<8;j++) {

				if (board[i][j] !=0) {

				if (board[i][j]->GetColor() == Player_Turn) {

					for(int k=0;k<8;k++) {

						for(int m=0;m<8;m++) {

							if (board[i][j]->move(i,j,k,m)) return true;
						}
					}
				}
			}
		}
		}
		cout<<"\nNo avalible moves left!\n";
		if (Player_Turn == 'B') cout<<"\nWhite player wins!\n";
		else cout<<"\nBlack player wins!\n";
		system("pause");
		return false;


	}


};


void Board::printStats_board() {

	cout<<"\n\nFigures in board :\n\n";

for(int i=0;i<8;i++) {
 
	for(int j=0;j<8;j++) {

		if (board[i][j]!=0){ Game::stats(i,j);cout<<"\n\n";}
	}
	}
	}





int main()
{
	setlocale(LC_ALL,"bulgarian");
	Game gm;
	gm.Start_game();
	
	system("pause");
	return 0;
}