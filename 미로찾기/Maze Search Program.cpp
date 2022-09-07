/* Maze Search Program
				미로 찾기 */

#include<iostream>
using namespace std;
#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

//좌표를 저장하기 위한 구조체 
typedef struct {
	short r;
	short c;
}element;

typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

//스택 초기화 함수 
void init(StackType* s)
{
	s->top = -1;
}

//공백 상태 검출 함수 
int is_stack_empty(StackType* s)
{
	return s->top == -1;
}

//포화 상태 검출 함수 
int is_full(StackType* s)
{
	return s->top == MAX_STACK_SIZE - 1;
}

//삽입함수 
void push(StackType* s, element value)
{
	if (is_full(s)) {
		exit(1);
	}
	s->stack[++(s->top)] = value;
}

//삭제 함수 
element pop(StackType* s)
{
	if (is_stack_empty(s)) {
		exit(1);
	}
	return s->stack[(s->top)--];
}

//피크 함수 
element peek(StackType* s)
{
	if (is_stack_empty(s)) {
		exit(1);
	}
	return s->stack[s->top];
}

element here = { 1,0 };
element entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};

//위치를 스택에 삽입 
void push_loc(StackType* s, int r, int c)
{
	// 배열 범위를 벗어난 r,c는 금지
	if (r < 0 || c < 0) return;
	// 벽(1)이 아니고, 이미 왔던 곳(.)이 아니다 = 갈 수 있다
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

//미로 화면에 출력
void print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	cout << endl;
	for (int i = 0; i < MAZE_SIZE; i++) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			cout << maze[i][j];
		}
		cout << endl;
	}
}

int main(void)
{
	int r, c;
	StackType s;

	init(&s);
	here = entry;
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		print(maze);

		// 스택은 가장 마지막에 넣은 것을 가장 먼저 뽑아준다
		// 그러므로 북-남-서-동 순서로 넣으면
		// 동-서-남-북 의 순서로 나오게 된다
		push_loc(&s, r - 1, c); // north
		push_loc(&s, r + 1, c); // south
		push_loc(&s, r, c - 1); // west
		push_loc(&s, r, c + 1); // east


		if (is_stack_empty(&s))
		{
			cout << "실패" << endl;
			exit(1);
		}
		else
			here = pop(&s);
	}
	cout << "성공" << endl;
	return 0;
}
