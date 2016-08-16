#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct subscriber
{
		unsigned long phone;
		char surname[20];
		char name[15];
		struct subscriber *next;
		struct subscriber *prev;
};

void add (struct subscriber** point, struct subscriber* value){
	struct subscriber* tmp;
	struct subscriber* tmp2; 
	if (*point == NULL)
    {
		tmp = (struct subscriber*)malloc(sizeof(struct subscriber));
		*point = tmp;
		tmp -> phone = value -> phone;
		strcpy (tmp -> surname, value -> surname);
		strcpy (tmp -> name, value -> name);
		tmp -> next = NULL;
		tmp -> prev = NULL;
	}
	else
    {
			tmp = *point;
			tmp2 = (struct subscriber*) malloc (sizeof (struct subscriber));
			tmp -> next = tmp2;
			tmp2 -> phone = value -> phone;
			strcpy (tmp2 -> surname, value -> surname);
			strcpy (tmp2 -> name, value -> name);
			tmp2 -> prev = tmp;
			tmp2 -> next = NULL;
			*point = tmp2;
	}
}

void del (struct subscriber* point)
{
	if (point == NULL)
    {
		return ;
	}
	if (point -> next != NULL)
    {
		del (point -> next);
	}
	free(point);
	point = NULL;	
}

void view(struct subscriber* point)
{
	while(point != NULL)
    {
		printf ("%lu\t%s\t%s", point -> phone, point -> surname, 
                point -> name);
		printf ("\n");
		point = point -> next;
	}
}

int search (struct subscriber** point, unsigned long phone)
{
	int index = 0;
	struct subscriber* tmp = *point;
	while (tmp != NULL)
    {
		if (tmp -> phone == phone)
        {
			printf ("%s\t%s\n", tmp -> surname, tmp -> name);
			return index;
		}
		index++;
		tmp = tmp -> next;
		if (tmp == NULL)
        {
			printf ("Phone not found!\n");
			return -1;
		}
	}
}

int delete (struct subscriber** point, struct subscriber** end, 
        unsigned long phone)
{
	int index = 0;
	struct subscriber* tmp = *point;
	while (tmp != NULL)
    {
		if(tmp -> phone == phone)
        {
			if(*point == tmp)
            {
				*point = tmp -> next;
				tmp -> next -> prev = NULL;
				free(tmp);
			} 
			else if (tmp -> next == NULL)
            {
					tmp -> prev -> next = NULL;
					*end = tmp -> prev;
					free(tmp);
			}
			else
            {
				tmp -> prev -> next = tmp -> next;
				tmp -> next -> prev = tmp -> prev;
				free(tmp);
			}
			return index;
		}
		index++;
		tmp = tmp -> next;
		if (tmp == NULL)
        {
		printf ("Phone not found!\n");
		return -1;
		}
	}
}

int main (void)
{
	struct subscriber *start = NULL;
	struct subscriber *end = NULL;
	struct subscriber *next = NULL;
	struct subscriber *prev = NULL;
	int num;
	struct subscriber *array;
	unsigned long test;

	while(1)
    {
		printf ("1 - add subscriber\n");
		printf ("2 - search subscriber\n");
		printf ("3 - delete subscriber\n");
		printf ("4 - view subscribers\n");
		printf ("5 - quit\n");
		scanf ("%d", &num);
		switch (num)
        {
			case 1:
				array = 
                    (struct subscriber*) malloc (sizeof(struct subscriber));
				printf ("Enter abonent date\n");
				scanf ("%lu", &array -> phone);
				scanf ("%s", array -> surname);
				scanf ("%s", array -> name);
				if (start == NULL)
                {
				    add (&start, array);
				    end = start;
				}
				else
                {
				    add (&end, array);
				}
				break;
			case 2:		
				printf ("Enter search phone\n");
				scanf ("%lu", &test);
				printf ("%d \n", search(&start, test));
				break;
			case 3:
				printf ("Enter search phone\n");
				scanf ("%lu", &test);
				printf ("%d \n", delete(&start, &end, test));
				break;
			case 4:
				view (start);
				break;
			case 5:
				break;
		}
	    if (num == 5)
        {
		    break;
	    }
    }	
del(start);
return 0;
}
