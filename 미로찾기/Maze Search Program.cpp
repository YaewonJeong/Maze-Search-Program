/* Maze Search Program
				�̷� ã�� */

#include<iostream>
using namespace std;
#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

//��ǥ�� �����ϱ� ���� ����ü 
typedef struct {
	short r;
	short c;
}element;

typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

//���� �ʱ�ȭ �Լ� 
void init(StackType* s)
{
	s->top = -1;
}

//���� ���� ���� �Լ� 
int is_stack_empty(StackType* s)
{
	return s->top == -1;
}

//��ȭ ���� ���� �Լ� 
int is_full(StackType* s)
{
	return s->top == MAX_STACK_SIZE - 1;
}

//�����Լ� 
void push(StackType* s, element value)
{
	if (is_full(s)) {
		exit(1);
	}
	s->stack[++(s->top)] = value;
}

//���� �Լ� 
element pop(StackType* s)
{
	if (is_stack_empty(s)) {
		exit(1);
	}
	return s->stack[(s->top)--];
}

//��ũ �Լ� 
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

//��ġ�� ���ÿ� ���� 
void push_loc(StackType* s, int r, int c)
{
	// �迭 ������ ��� r,c�� ����
	if (r < 0 || c < 0) return;
	// ��(1)�� �ƴϰ�, �̹� �Դ� ��(.)�� �ƴϴ� = �� �� �ִ�
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

//�̷� ȭ�鿡 ���
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

		// ������ ���� �������� ���� ���� ���� ���� �̾��ش�
		// �׷��Ƿ� ��-��-��-�� ������ ������
		// ��-��-��-�� �� ������ ������ �ȴ�
		push_loc(&s, r - 1, c); // north
		push_loc(&s, r + 1, c); // south
		push_loc(&s, r, c - 1); // west
		push_loc(&s, r, c + 1); // east


		if (is_stack_empty(&s))
		{
			cout << "����" << endl;
			exit(1);
		}
		else
			here = pop(&s);
	}
	cout << "����" << endl;
	return 0;
}
