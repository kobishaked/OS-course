//enums
typedef enum Polygon_type { HEXAGON = 6, HEPTAGON, OCTAGON }Polygon_type;
enum name_func {ADD_POLYGON, PRINT_POLYGON, PRINT_PERIMETER, PRINT_DIAGONALS, PRINT_AREA};

//structs
typedef struct command {
	unsigned char finish;
	unsigned char newPoly;
	unsigned char type;
	unsigned char typeAction;
	unsigned char perimAction;
	unsigned char areaAction;
	unsigned char diagAction;
	unsigned char shapes;
} command;

typedef struct Point {
	char x;
	char y;
}Point;

typedef struct Polygon {
	Polygon_type type;
	Point points[8];
}Polygon;

typedef struct node {
	Polygon* poly;
	struct node* next;
}node;

//functions prototypes
Polygon* parseCoordinate(Polygon* p, long long cor1, long long cor2);
struct command parseCommand(unsigned long long hex);
Polygon* create_poly(long long cor1, long long cor2);
void print_polygon(Polygon* p);
void print_points(Polygon* p);
void add_polygon(Polygon* p);
float caluclate_distance(int x1, int y1, int x2, int y2);
void print_perimeter(Polygon* p);
void print_diagonals(Polygon* p);
void print_area(Polygon* p);
void print_list(command* cmd);
void print_actions(node* n, command* cmd);
void free_list();