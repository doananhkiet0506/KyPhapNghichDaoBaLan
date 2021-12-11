#include <iostream>
#include <string>
using namespace std;

/** Vùng cài đặt struct node **/
struct nodeChar
{
	char ch;
	nodeChar *pNext;
};

struct nodeDouble
{
	double doubleData;
	nodeDouble *pNext;
};

nodeChar* createNodeChar(char ch)
{
	nodeChar *pNode = new nodeChar;
	if (pNode == nullptr)
		return nullptr;
	pNode->ch = ch;
	pNode->pNext = nullptr;
	return pNode;
}

nodeDouble* createNodeDouble(double doubleData)
{
	nodeDouble *pNode = new nodeDouble;
	if (pNode == nullptr)
		return nullptr;
	pNode->doubleData = doubleData;
	pNode->pNext = nullptr;
}


/** Vùng cài đặt STACK Bước Đệm **/
struct stackBuocDem
{
	nodeChar *pTop;
};

void createStackBuocDem(stackBuocDem &s)
{
	s.pTop = nullptr;
}

bool isEmptyStackBuocDem(stackBuocDem s)
{
	if (s.pTop == nullptr)
		return true;
	return false;
}

bool pushStackBuocDem(stackBuocDem &s, nodeChar *pNode)
{
	if (pNode == nullptr)
		return false;
	if (isEmptyStackBuocDem(s))
		s.pTop = pNode;
	else
	{
		pNode->pNext = s.pTop;
		s.pTop = pNode;
	}
	return true;
}

bool popStackBuocDem(stackBuocDem &s, char &ch)
{
	if (isEmptyStackBuocDem(s))
		return false;
	ch = s.pTop->ch;
	nodeChar *temp = s.pTop;
	s.pTop = s.pTop->pNext;
	delete temp;
	return true;
}

bool topStackBuocDem(stackBuocDem s, char &ch)
{
	if (isEmptyStackBuocDem(s))
		return false;
	ch = s.pTop->ch;
	return true;
}

/** Vùng cài đặt STACK Kết Quả **/
struct stackKetQua
{
	nodeDouble *pTop;
};

void createStackKetQua(stackKetQua &stackKQ)
{
	stackKQ.pTop = nullptr;
}

bool isEmptyStackKetQua(stackKetQua stackKQ)
{
	if (stackKQ.pTop == nullptr)
		return true;
	return false;
}

bool pushStackKetQua(stackKetQua &stackKQ, nodeDouble *pNode)
{
	if (pNode == nullptr)
		return false;
	if (isEmptyStackKetQua(stackKQ))
		stackKQ.pTop = pNode;
	else
	{
		pNode->pNext = stackKQ.pTop;
		stackKQ.pTop = pNode;
	}
	return true;
}

bool popStackKetQua(stackKetQua &stackKQ, double &doubleData)
{
	if (isEmptyStackKetQua(stackKQ))
		return false;
	doubleData = stackKQ.pTop->doubleData;
	nodeDouble *temp = stackKQ.pTop;
	stackKQ.pTop = stackKQ.pTop->pNext;
	delete temp;
	return true;
}

bool topStackKetQua(stackKetQua stackKQ, double &doubleData)
{
	if (isEmptyStackKetQua(stackKQ))
		return false;
	doubleData = stackKQ.pTop->doubleData;
	return true;
}

/** Vùng cài đặt QUEUE Biểu Thức **/
struct queueBieuThuc
{
	nodeChar *pHead;
	nodeChar *pTail;
};

void createQueueBieuThuc(queueBieuThuc &q)
{
	q.pHead = q.pTail = nullptr;
}

bool isEmptyQueueBieuThuc(queueBieuThuc q)
{
	if (q.pHead == nullptr)
		return true;
	return false;
}

bool enQueueBieuThuc(queueBieuThuc &q, nodeChar *pNode)
{
	if (pNode == nullptr)
		return false;
	if (isEmptyQueueBieuThuc(q))
		q.pHead = q.pTail = pNode;
	else
	{
		q.pTail->pNext = pNode;
		q.pTail = pNode;
	}
	return true;
}

bool deQueueBieuThuc(queueBieuThuc &q, char &ch)
{
	if (isEmptyQueueBieuThuc(q))
		return false;
	ch = q.pHead->ch;
	nodeChar *temp = q.pHead;
	q.pHead = q.pHead->pNext;
	delete temp;
	return true;
}

bool frontQueueBieuThuc(queueBieuThuc q, char &ch)
{
	if (isEmptyQueueBieuThuc(q))
		return false;
	ch = q.pHead->ch;
	return true;
}

/** Vùng cài đặt Ký pháp nghịch đảo Ba Lan **/
void chuyenTrungToSangHauTo(stackBuocDem &stackBD, queueBieuThuc &queueBT, string bieuthuc)
{
	// Duyệt từng kí tự trong biểu thức
	for (int i = 0; i < bieuthuc.length(); i++)
	{
		//Nếu là toán hạng thì thêm vào queueBieuThuc
		if (bieuthuc[i] >= '0' && bieuthuc[i] <= '9')
		{
			nodeChar *pNode = createNodeChar(bieuthuc[i]);
			enQueueBieuThuc(queueBT, pNode);
		}
		//Nếu là dấu mở ngoặc thì push vào trong stackBuocDem
		else if (bieuthuc[i] == '(')
		{
			nodeChar *pNode = createNodeChar(bieuthuc[i]);
			pushStackBuocDem(stackBD, pNode);
		}
		/*
			Nếu là dấu đóng ngoặc thì lấy tất cả phần tử trong stackBuocDem và them vao
			queueBieuThuc cho đến khi gặp dấu '(' thì dừng. Sau đó loại bỏ '(' ra khỏi 
			stackBD
		*/
		else if (bieuthuc[i] == ')')
		{
			char ch;
			nodeChar *pNode;

			while (true)
			{
				popStackBuocDem(stackBD, ch);
				if (ch == '(')
					break;
				nodeChar *pNode = createNodeChar(ch);
				enQueueBieuThuc(queueBT, pNode);
			}
		}
		//Nếu là toán tử: + - * /
		else if (bieuthuc[i] == '+' || bieuthuc[i] == '-' || bieuthuc[i] == '*' || bieuthuc[i] == '/')
		{
			//Nếu stackBD đang rỗng thì push bieuthuc[i] vào stackBD
			if (isEmptyStackBuocDem(stackBD))
			{
				nodeChar *pNode = createNodeChar(bieuthuc[i]);
				pushStackBuocDem(stackBD, pNode);
			}
			//Đang có phần tử
			else
			{
				char ch;
				topStackBuocDem(stackBD, ch);
				//Nếp phần tử đầu stackBD là toán tử thì kiểm tra độ ưu tiên toán tử
				if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
				{
					//Nếu toán tử đầu stackBD (ch) có độ ưu tiên < bieuthuc[i] thì push bieuthuc[i] vào stackBD
					if ((ch == '+' || ch == '-') && (bieuthuc[i] == '*' || bieuthuc[i] == '/'))
					{
						nodeChar *pNode = createNodeChar(bieuthuc[i]);
						pushStackBuocDem(stackBD, pNode);
					}

					/*
						Nếu toán tử đầu stackBD (ch) có độ ưu tiên >= bieuthuc[] thì:
						- Nếu ch có độ ưu tiên >= bieuthuc[i] thì lấy
						phần tử đầu stackBD them vào trong. LẶP LẠI như vậy cho đến stackBD rỗng
						hoặc phần tử đầu stack không là toán tử nữa => stack không rỗng, đồng thời phần tử đầu stack là toán tử thì tiếp tục vòng lặp
						- Sau đó push bieuthuc[i] vào stackBD
						*/
					//=================================================================================
					else if (	((ch == '*' || ch == '/') && (bieuthuc[i] == '+' || bieuthuc[i] == '-'))
							 || ((ch == '+' || ch == '-') && (bieuthuc[i] == '+' || bieuthuc[i] == '-'))
							 || ((ch == '*' || ch == '/') && (bieuthuc[i] == '*' || bieuthuc[i] == '/')))
							
					{
						//StackBD không rỗng hoặc phần tử đầu StackBD vẫn là toán tử thì tiếp tục vòng lặp
						while (!isEmptyStackBuocDem(stackBD) && (ch == '+' || ch == '-' || ch == '*' || ch == '/'))
						{
							if (((ch == '*' || ch == '/') && (bieuthuc[i] == '+' || bieuthuc[i] == '-'))
								|| ((ch == '+' || ch == '-') && (bieuthuc[i] == '+' || bieuthuc[i] == '-'))
								|| ((ch == '*' || ch == '/') && (bieuthuc[i] == '*' || bieuthuc[i] == '/')))
							{
								popStackBuocDem(stackBD, ch);

								nodeChar *pNode = createNodeChar(ch);
								enQueueBieuThuc(queueBT, pNode);

								topStackBuocDem(stackBD, ch);
							}
							else
							{
								break;
							}
						}
						nodeChar *pNode = createNodeChar(bieuthuc[i]);
						pushStackBuocDem(stackBD, pNode);
					}
				}
				
				// Phần tử đầu stackBD không là toán tử thì push bieuthuc[i] vào stackBD
				else
				{
					nodeChar *pNode = createNodeChar(bieuthuc[i]);
					pushStackBuocDem(stackBD, pNode);
				}
			}
		}
	}

	//Duyệt hết vòng lặp rồi mà trong stackBD vẫn còn phần tử thì lấy ra tất cả và thêm vào queueBT
	char ch;
	nodeChar *pNode;
	while (!isEmptyStackBuocDem(stackBD))
	{
		popStackBuocDem(stackBD, ch);

		pNode = createNodeChar(ch);
		enQueueBieuThuc(queueBT, pNode);
	}
}

double tinhToanBieuThucHauTo(stackKetQua &stackKQ, queueBieuThuc queueBT)
{
	for (nodeChar *i = queueBT.pHead; i != nullptr; i = i->pNext)
	{
		if (i->ch >= '0' && i->ch <= '9')
		{
			nodeDouble *pNode = createNodeDouble(static_cast<double>(i->ch) - 48);
			pushStackKetQua(stackKQ, pNode);
		}
		else
		{
			double p1, p2; //p1 p2 là 2 toán hạng lấy ra lần lượt trong stackKQ
			popStackKetQua(stackKQ, p1);
			popStackKetQua(stackKQ, p2);

			nodeDouble *pNode = nullptr;
			if (i->ch == '+')
			{
				pNode = createNodeDouble(p2 + p1);
			}
			else if (i->ch == '-')
			{
				pNode = createNodeDouble(p2 - p1);
			}
			else if (i->ch == '*')
			{
				pNode = createNodeDouble(p2 * p1);
			}
			else if (i->ch == '/')
			{
				pNode = createNodeDouble(p2 / p1);
			}
			
			pushStackKetQua(stackKQ, pNode);
		}
	}

	return stackKQ.pTop->doubleData;
}

/** Vùng cài đặt nhập xuất biểu thức **/
string nhapBieuThuc()
{
	string bt;
	cout << "Nhap bieu thuc: ";
	getline(cin, bt);
	return bt;
}

void inBieuThucHauTo(queueBieuThuc queueBT)
{
	for (nodeChar *i = queueBT.pHead; i != nullptr; i = i->pNext)
	{
		cout << i->ch;
	}
}
int main()
{
	stackBuocDem stackBD;
	queueBieuThuc queueBT;
	stackKetQua stackKQ;

	createStackBuocDem(stackBD);
	createQueueBieuThuc(queueBT);

	string bieuthuc = nhapBieuThuc();

	chuyenTrungToSangHauTo(stackBD, queueBT, bieuthuc);
	
	cout <<"\nBieu thuc trung to: " << bieuthuc << endl;
	cout << "Bieu thuc hau to: ";

	inBieuThucHauTo(queueBT);
	cout << "\nKet qua = " << tinhToanBieuThucHauTo(stackKQ, queueBT) << endl;
	system("pause");
	//Biểu thức để test: (5+6/2)*3 + 8/2 -> 562/+3*82/+ -> kết quả: 28
	return 0;
}