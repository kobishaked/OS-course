#include "ex1_q1.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

node* tail = NULL;
node* head = NULL;
void(*func_ptr[5])(Polygon* p) = {add_polygon, print_polygon, print_perimeter, print_diagonals, print_area};
int main() {
	command cmd;
	while (1)
	{

		unsigned long long com;
		long long cor1;
		long long cor2;
		scanf("%llx", &com); // read command
		cmd = parseCommand(com);
		if (cmd.newPoly)					//if new poly get the parse the coords, make new poly struct and add to the list 
		{
			scanf("%llx", &cor1);
			scanf("%llx", &cor2);
			Polygon* new;
			new = create_poly(cor1, cor2);
			new->type = cmd.type;
			func_ptr[ADD_POLYGON](new);
			if (cmd.shapes == 0) {			// case that dont need to print more nodes from the list
				print_actions(tail, &cmd);
			}
		}
		if (cmd.shapes != 0) {				// case to run the list and print more data from it
			print_list(&cmd);
		}
		if (cmd.finish == 1) {
			free_list();
			break;
		}
	}
	return 0;

}

// function thats get hex number and return parse struct. calling from main func
command parseCommand(unsigned long long hex) {
	command com;
	com.finish = 0b00000000000001 & hex;
	com.newPoly = (0b00000000000010 & hex) >> 1;
	com.type = (0b00000000111100 & hex) >> 2;
	com.typeAction = (0b00000001000000 & hex) >> 6;
	com.perimAction = (0b00000010000000 & hex) >> 7;
	com.areaAction = (0b00000100000000 & hex) >> 8;
	com.diagAction = (0b00001000000000 & hex) >> 9;
	com.shapes = (0b11110000000000 & hex) >> 10;
	return com;
}

//get the 2 coord from the input and return new poly with his coordinates
Polygon* create_poly(long long cor1, long long cor2) {
	Polygon* new_poly = (Polygon*)malloc(sizeof(Polygon));
	return parseCoordinate(new_poly, cor1, cor2);
}

// function thats get hex number and parse it to coordinate. calling from create_poly func
Polygon* parseCoordinate(Polygon* p, long long cor1, long long cor2) {
	p->points[0].x = 0x00000000000000ff & cor1;
	p->points[0].y = (0x000000000000ff00 & cor1) >> 8;
	p->points[1].x = (0x0000000000ff0000 & cor1) >> 16;
	p->points[1].y = (0x00000000ff000000 & cor1) >> 24;
	p->points[2].x = (0x000000ff00000000 & cor1) >> 32;
	p->points[2].y = (0x0000ff0000000000 & cor1) >> 40;
	p->points[3].x = (0x00ff000000000000 & cor1) >> 48;
	p->points[3].y = (0xff00000000000000 & cor1) >> 56;
	p->points[4].x = 0x00000000000000ff & cor2;
	p->points[4].y = (0x000000000000ff00 & cor2) >> 8;
	p->points[5].x = (0x0000000000ff0000 & cor2) >> 16;
	p->points[5].y = (0x00000000ff000000 & cor2) >> 24;
	p->points[6].x = (0x000000ff00000000 & cor2) >> 32;
	p->points[6].y = (0x0000ff0000000000 & cor2) >> 40;
	p->points[7].x = (0x00ff000000000000 & cor2) >> 48;
	p->points[7].y = (0xff00000000000000 & cor2) >> 56;
	return p;
}

//add poly to the end of the list
void add_polygon(Polygon* p) {
	node* new_node = (node*)malloc(sizeof(node));
	new_node->poly = p;
	if (head == NULL) {
		head = new_node;
	}
	if (tail == NULL) {
		tail = new_node;
	}
	else {
		tail->next = new_node;
	}
	new_node->next = NULL;
	tail = new_node;
}

//run the list and for each shape that need to print something call the print_action func
void print_list(command* cmd) {
		node* current = head;
		while (current) {
			print_actions(current, cmd);
			current = current->next;
			}
		}

//check the actions that need to do from the command at this specific node. calling from the main (if print just the new poly) or from print_list func if need to run the list
void print_actions(node* n, command* cmd) {
	if (cmd->shapes == n->poly->type || cmd->shapes == 0 || cmd->shapes == 15) {
		if (cmd->typeAction) {
			func_ptr[PRINT_POLYGON](n->poly);
		}
		if (cmd->perimAction) {
			func_ptr[PRINT_PERIMETER](n->poly);
		}
		if (cmd->areaAction) {
			func_ptr[PRINT_AREA](n->poly);
		}
		if (cmd->diagAction) {
			func_ptr[PRINT_DIAGONALS](n->poly);
		}
	}
}

//print poly data (name and points)
void print_polygon(Polygon* p) {
	switch (p->type) {
	case 6:printf("hexagon ");
		print_points(p);
		break;
	case 7:printf("heptagon ");
		print_points(p);
		break;
	case 8:printf("octagon ");
		print_points(p);
		break;
	}
}

//print the point of the poly, calling from print_polygon func
void print_points(Polygon* p) {
	for (int i = 0; i < p->type; i++) {
		printf("{%d, %d} ", p->points[i].x, p->points[i].y);
	}
	printf("\n");
}

void print_perimeter(Polygon* p) {
	int i;
	float perimeter = 0;
	for (i = 0; i < p->type-1; ++i) {
		perimeter += caluclate_distance(p->points[i].x, p->points[i].y, p->points[i+1].x, p->points[i+1].y);
	}
	perimeter += caluclate_distance(p->points[0].x, p->points[0].y, p->points[p->type-1].x, p->points[p->type - 1].y);
	printf("perimeter = %.1f\n", perimeter);
}

void print_diagonals(Polygon* p) {
	int i, j;
	float diagonals = 0;
	for (i = 0; i < p->type; ++i) {
		for (j = i; j < p->type; ++j) {
			if (!(abs(i - j) == 1 || i == j || abs(i - j) == (p->type - 1))) {
				diagonals += caluclate_distance(p->points[i].x, p->points[i].y, p->points[j].x, p->points[j].y);
			}
		}
	}
	printf("diagonals = %.1f\n", diagonals);

}

void print_area(Polygon* p) {
	float area = 0;
	int i;
	for (i = 1; i < p->type + 1; ++i) {
		area += p->points[i % p->type].x * (p->points[(i + 1) % p->type].y - p->points[(i - 1) % p->type].y);
	}
	area = fabs(area / 2.0f);
	printf("area = %.1f\n", area);
}

//return the distance from 2 specific points of a specific poly 
float caluclate_distance(int x1, int y1, int x2, int y2) {
	float res;
	res = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	return res;
}

void free_list() {
	node* current;
	node* temp;
	current = head;
	while (current != NULL) {
		temp = current->next;
		free(current->poly);
		free(current);
		current = temp;
	}
}

