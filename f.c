#include <stdio.h>
#include <termio.h>
#include <stdlib.h>
#include <unistd.h>

int getch(void){
        int ch;
        struct termios buf;
        struct termios save;
        tcgetattr(0 , &save);
        buf = save;
        buf.c_lflag&=~(ICANON|ECHO);
        buf.c_cc[VMIN] = 1;
        buf.c_cc[VTIME] = 0;
        tcsetattr(0, TCSAFLUSH, &buf);
        ch = getchar();
        tcsetattr(0, TCSAFLUSH, &save);
        return ch; }

        int main(void){

                char c,letter, input_char;
                FILE *go;
                int line=0 ,row=0, box_line=1 ,box_row=1, count=0;

                go = fopen("jong.txt", "r");
                char memorize[10][10][10];
                                int Ocount = -1;
                                int O[20] = {0};

                while ((letter = getc(go)) != EOF){

                        memorize[0][0][count]=letter;
                        count++;

                        if (letter == '\n')
                                ++box_row;
                        if (box_row==1)
                                ++box_line;
                        if (letter=='@'){
                                row = box_row-1;
                                line = (count+1) % box_line-2;
                        }
                                if (letter == 'O')
                                                {
                                                        Ocount += 1;
                                                        O[Ocount] = count-1;
                                                }

                                }

                char player[box_row][box_line];

                for(int i=0 ; i<=box_row*box_line-2 ;i++ )
                        player[0][i] = memorize[0][0][i];

                system("clear");

                for (int i=0; i<=box_line*box_row; i++)
                                        printf("%c", player[0][i]);

                                printf("%d\n", Ocount);
                                for(int i=0; i<=Ocount;i++)
                                        printf("%d\n",O[i]);

                while (1){
                        input_char = getch();
                        if (input_char == 'q'){
                                printf("Bye\n");
                                break;      }
                        else{
                                switch (input_char) {
                                  case 'k':{
                                    FILE *fp3;
                                    char ch;
                                    fp3 = fopen("sokoban.txt", "w");
                                    printf("k \n");
                                    sleep(1);
                                    printf("도움말을 보여줍니다 \n");
                                    sleep(1);

                                    for (int i=0; i<=box_line*box_row; i++)
                                            fprintf(fp3,"%c", player[0][i]);
                                    system("clear") ;

                                  fclose(fp3);
                                   printf("\n\n\n\na(왼쪽), s(아래), w(위), d(오른쪽)\n");
                                   printf("u(undo)\n");
                                   printf("r(replay)\n");
                                   printf("n(new)\n");
                                   printf("e(exit)\n");
                                   printf("l(save)\n");
                                   printf("f(file load)\n");
                                   printf("k(display help)\n");
                                   printf("t(top)\n\n\n\n\n\n");
                                   printf("맵으로 돌아가실거면 아무키나 눌러주세요\n");

                                    getch();
                                    system("clear") ;

                                    fp3=fopen("sokoban.txt","r");

                                    line=0 ,row=0, box_line=1 ,box_row=1, count=0;
                                    int Ocount = -1;
                                    int O[20] = {0};
                                    while ((letter = getc(fp3)) != EOF){

                                            memorize[0][0][count]=letter;
                                            count++;

                                            if (letter == '\n')
                                                    ++box_row;
                                            if (box_row==1)
                                                    ++box_line;
                                            if (letter=='@'){
                                                    row = box_row-1;
                                                    line = (count+1) % box_line-2;
                                            }
                                                    if (letter == 'O')
                                                                    {
                                                                            Ocount += 1;
                                                                            O[Ocount] = count-1;
                                                                    }

                                                    }
                                                    for(int i=0 ; i<=box_row*box_line-2 ;i++ )
                                                            player[0][i] = memorize[0][0][i];


                                                    system("clear");


                                                    for (int i=0; i<=box_line*box_row; i++)
                                                                            printf("%c", player[0][i]);

                                                                    printf("%d\n", Ocount);
                                                                    for(int i=0; i<=Ocount;i++)
                                                                            printf("%d\n",O[i]);

                                    fclose(fp3);
                                    break;
                                  }
                                        case 'd' : {
                                                           if(player[row][line+1] == '#')
                                                                   break;
                                                           if(player[row][line+1] == '$')
                                                           {
                                                                   if(player[row][line+2] == '#' || player[row][line+2] == '$')
                                                                           break;
                                                                   line += 1;
                                                                   player[row][line-1] = ' ';
                                                                   player[row][line] = '@';
                                                                   player[row][line+1] = '$';
                                                                   break;
                                                           }

                                                           player[row][line] =' ';
                                                           line+=1;
                                                           player[row][line] ='@';

                                                   }

                                                   break;

                                        case 'a' : {
                                                           if(player[row][line-1] == '#')
                                                                   break;
                                                           if(player[row][line-1] == '$')
                                                           {
                                                                   if(player[row][line-2] == '#' || player[row][line-2] == '$')
                                                                           break;
                                                                   line -= 1;
                                                                   player[row][line+1] = ' ';
                                                                   player[row][line] = '@';
                                                                   player[row][line-1] = '$';
                                                                   break;
                                                           }
                                                           player[row][line] =' ';
                                                           line-=1;
                                                           player[row][line] ='@';}
                                                   break;


                                        case 'w' : {
                                                           if(player[row-1][line] == '#')
                                                                   break;
                                                           if(player[row-1][line] == '$')
                                                           {
                                                                   if(player[row-2][line] == '#' || player[row-2][line] == '$')
                                                                           break;
                                                                   row -= 1;
                                                                   player[row+1][line] = ' ';
                                                                   player[row][line] = '@';
                                                                   player[row-1][line] = '$';
                                                                   break;
                                                           }
                                                           player[row][line] =' ';
                                                           row-=1;
                                                           player[row][line] ='@';}
                                                   break;
                                        case 's' : {
                                                           if(player[row+1][line] == '#')
                                                                   break;
                                                           if(player[row+1][line] == '$')
                                                           {
                                                                   if(player[row+2][line] == '#' || player[row+2][line] == '$')
                                                                           break;
                                                                   row += 1;
                                                                   player[row-1][line] = ' ';
                                                                   player[row][line] = '@';
                                                                   player[row+1][line] = '$';
                                                                   break;
                                                           }
                                                           player[row][line] =' ';
                                                           row+=1;
                                                           player[row][line] ='@';}
                                                   break;


						                      case 'l' : {

                                                                      FILE *fp;

                                                           fp = fopen("sokoban.txt", "w");
                                                           printf("l \n");
                                                            sleep(1);

                                                           printf("파일을 저장했습니다\n");
                                                            sleep(1);

                                                      for (int i=0; i<=box_line*box_row; i++)
                                                       fprintf(fp,"%c", player[0][i]);


                                                          fclose(fp);

                                                            break;


                                                                   }

                                 case 'f' : {

                                                FILE*fp1;
                                             fp1=fopen("sokoban.txt","r");
                                             printf("f \n");
                                             sleep(1);
                                             printf("저장된 파일을 불러오겠습니다\n");
                                             sleep(1);
                                             line=0 ,row=0, box_line=1 ,box_row=1, count=0;
                                             int Ocount = -1;
                                             int O[20] = {0};
                                             while ((letter = getc(fp1)) != EOF){

                                                     memorize[0][0][count]=letter;
                                                     count++;



                                                     if (letter == '\n')
                                                             ++box_row;
                                                     if (box_row==1)
                                                             ++box_line;
                                                     if (letter=='@'){
                                                             row = box_row-1;
                                                             line = (count+1) % box_line-2;
                                                     }
                                                             if (letter == 'O')
                                                                             {
                                                                                     Ocount += 1;
                                                                                     O[Ocount] = count-1;
                                                                             }

                                                             }
                                                             for(int i=0 ; i<=box_row*box_line-2 ;i++ )
                                                                     player[0][i] = memorize[0][0][i];


                                                             system("clear");


                                                             for (int i=0; i<=box_line*box_row; i++)
                                                                                     printf("%c", player[0][i]);

                                                                             printf("%d\n", Ocount);
                                                                             for(int i=0; i<=Ocount;i++)
                                                                                     printf("%d\n",O[i]);

                                             fclose(fp1);
                                             break;
                                           }


                               case 'r' : {
                                             FILE*fp2;
                                             fp2=fopen("jong.txt", "r");
                                             printf("r\n");
                                             sleep(1);
                                             printf("처음부터 다시 시작합니다\n");
                                             sleep(1);
                                             line=0 ,row=0, box_line=1 ,box_row=1, count=0;
                                             int Ocount = -1;
                                             int O[20] = {0};
                                             while ((letter = getc(fp2)) != EOF){

                                                     memorize[0][0][count]=letter;
                                                     count++;



                                                     if (letter == '\n')
                                                             ++box_row;
                                                     if (box_row==1)
                                                             ++box_line;
                                                     if (letter=='@'){
                                                             row = box_row-1;
                                                             line = (count+1) % box_line-2;
                                                     }
                                                             if (letter == 'O')
                                                                             {
                                                                                     Ocount += 1;
                                                                                     O[Ocount] = count-1;
                                                                             }

                                                             }
                                                             for(int i=0 ; i<=box_row*box_line-2 ;i++ )
                                                                     player[0][i] = memorize[0][0][i];


                                                             system("clear");


                                                             for (int i=0; i<=box_line*box_row; i++)
                                                                                     printf("%c", player[0][i]);

                                                                             printf("%d\n", Ocount);
                                                                             for(int i=0; i<=Ocount;i++)
                                                                                     printf("%d\n",O[i]);
                                             fclose(fp2);
                                             break;
                                           }

                                        }


                                                               system("clear");
                                int n = 0;
                                                                for(n=0;n<=Ocount;n++)
                                                                {
                                                                        if(player[0][O[n]] == ' ' || player[0][O[n]] == 0)
                                                                           player[0][O[n]] = 'O';
                                                                }

                                                                for (int i = 0; i<box_row*box_line-1 ;i++){
                                                                        if(player[0][i] == 0)
                                                                                printf("%c", ' ');
                                                                        else
                                                printf("%c", player[0][i] );
                                }
                                printf("\n");
                                                }
                                                }
                                                  fclose(go);
                                return 0;
        }
