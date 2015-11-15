int id();
void manageitem();
void additem();
void displayallitem();
void purchaseitem();
void finalbill();
int billno();
struct item finditem(int id);
struct item finditem(int);

void updateitem(int ,int);

char fitem[] = {"item.dat"};
char fbill[] = {"bill.dat"};

int sum = 0;


struct item{
	int id;
	char name[40];
	int cost;
	int qty;
	};



struct bill{
	int nid;
	char nname[40];
	int ncost;
	};


