#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

Node
*create_new_node(int data) {
	Node *new_node = (Node *)malloc(sizeof (Node));
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

Node
*create_circular_linked_list(N) {
	Node *head = (Node *)malloc(sizeof *head), *first_node = NULL;
	head->data = 1;
	first_node = head;

	for (int i = 2; i < N; i++) {
		head->next = (Node *)malloc(sizeof *head);
		head = head->next;
		head->data = i;
		printf("head->data: %d\n", head->data);
	}

	// Point the last node to the first, complete the list
	head->next = first_node;
	//head = first_node;
	return head;
}

void 
*add_node_to_front(Node **head, int data) {
	Node *new_node = (Node *)malloc(sizeof (Node));
	
	new_node->data = data;
	
	// Makes the new node head
	new_node->next = *head;

	// Move head pointer to new node
	*head = new_node;
}

void 
*add_node_to_end(Node **head, int data) {
	Node *new_node = (Node *)malloc(sizeof (Node));
	Node *last_node = *head;
	
	new_node->data = data;
	new_node->next = NULL;

	while (last_node->next != NULL){
		last_node = last_node->next;
	}

	last_node->next = new_node;

	// Using Node *head
	//while (head != NULL) {
	//	if (head->next == NULL) {
	//		head->next = new_node;
	//	}
	//	head = head->next;
	//}
}

void
*insert_node_after(Node *node, Node* new_node) {
	if (node == NULL) {
		fprintf(stderr, "Node is NULL\n");
	}

	new_node->next = node->next;
	node->next = new_node;
}

void
delete_beg(Node **head) {
	Node *tmp = (*head);
	(*head) = (*head)->next;
	free(tmp);
}

void
delete_end(Node **head) {
	Node *end = (*head);
	Node *prev = NULL;
	while (end->next != NULL) {
		prev = end;
		end = end->next;
	}
	prev->next = NULL;
	free(end);
}

void
delete_in_middle(Node **head) {
	Node *ahead_p = *head;
	Node *behind_p = *head;
	Node *tmp = NULL;

	if (*head != NULL) {
		while (ahead_p->next != NULL && ahead_p->next->next != NULL) {
			if (ahead_p->next->next != NULL) {
				// Keep saving a reference to the node behind the middle node
				tmp = behind_p;
			}
			ahead_p = ahead_p->next->next;
			behind_p = behind_p->next;
		}
	}
	tmp->next = behind_p->next;
	printf("Deleted middle node %d. Middle node is now %d\n", behind_p->data, tmp->data);
	free(behind_p);
}

Node
*reverse_linked_list(Node **head) {
	Node *previous_p = NULL;
	Node *current_p = (*head);
	Node *ahead_p = (*head)->next;

	if (*head != NULL) {
		while(current_p != NULL) {
			// Preserve next node
			ahead_p = current_p->next;

			// Point to previous node
			current_p->next = previous_p;

			// Set previous node to current node
			previous_p = current_p;

			// Set next node to current
			current_p = ahead_p;
		}
	}

	// Will ultimately be the final node
	return previous_p;
}

Node
*merge_sorted_linked_lists(Node **list1, Node **list2) {
	/* Return one sorted link list */
	
	// New head
	Node *head = NULL;

	// Head points to list based on which one contains
	// lowest value, because it needs to be returned sorted
	if ((*list1)->data <= (*list2)->data) {
		head = (*list1);
		(*list1) = (*list1)->next;
	}
	else {
		head = (*list2);
		(*list2) = (*list2)->next;
	}

	Node *current_p = head;

	while (*list1 != NULL && *list2 != NULL) {
		// Point current node to the lowest value in one of
		// the linked lists
		if ((*list1)->data <= (*list2)->data) {
			current_p->next = (*list1);
			(*list1) = (*list1)->next;
		} 
		else {
			current_p->next = (*list2);
			(*list2) = (*list2)->next;
		}
		current_p = current_p->next;
	}

	// One of the linked lists might be finish first
	// Figure out which one it is and simply point to it
	// to finish off the linked list
	if ((*list1) == NULL) {
		current_p->next = (*list2);
	} 
	else {
		current_p->next = (*list1);
	}
	
	return head;
}

void 
*print_linked_list(Node *head) {
	Node *tmp = head;
	while (tmp != NULL) {
		printf("%d - ", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
}

void 
*print_circular_linked_list(Node *head) {
	Node *tmp = head->next;
	Node *first_node = head;
	while (tmp != head) {
		printf("%d - ", tmp->data);
		tmp = tmp->next;
	}
	printf("%d - ", first_node->data);
	printf("\n");
}

Node
*find_node(Node *head, int data) {
	Node *tmp = head;
	while (tmp != NULL) {
		if (tmp->data == data) {
			return tmp;
		}
		tmp = tmp->next;
	}
	fprintf(stderr, "Node %d not found.\n", tmp->data);
	return head;
}

void
print_middle(Node *head) {
	Node *ahead_p = head;
	Node *behind_p = head;

	if (head != NULL) {
		while (ahead_p->next != NULL && ahead_p->next->next != NULL) {
			ahead_p = ahead_p->next->next;
			behind_p = behind_p->next;
		}
	}
	printf("Middle node is %d\n", behind_p->data);
}

bool
is_circular_linked_list(Node *head) {
	Node *tmp = head->next;
	
	// Store traversed nodes
	int prev[32];
	int counter = 0;

	while (tmp != NULL) {
		prev[counter++] = tmp->data;

		for (int i = 0; i < counter; i++) {
			// Check if the next node has been seen previously
			if (tmp->next->data == prev[i]) {
				return true;
			}
		}
		tmp = tmp->next;
	}

	return false;
}

int main(int argc, char *argv[]) {

	Node *head = NULL;
	Node *head2 = NULL;

	for (int i = 0; i < 11; i++) {
		add_node_to_front(&head, i);
	}
	printf("Added 10 nodes to the front on the list\n");
	print_linked_list(head);

	insert_node_after(find_node(head, 5), create_new_node(88));
	printf("Inserted a node after 5\n");
	print_linked_list(head);

	printf("Added a node to end of list\n");
	add_node_to_end(&head, 11);
	print_linked_list(head);

	printf("Deleted a node at the beginning of the list\n");
	delete_beg(&head);
	print_linked_list(head);

	printf("Deleted a node at the end of the list\n");
	delete_end(&head);
	print_linked_list(head);

	print_middle(head);

	delete_in_middle(&head);
	print_middle(head);
	print_linked_list(head);

	printf("Reverse the linked list\n");
	head = reverse_linked_list(&head);
	print_linked_list(head);

	printf("Create another linked list\n");
	head2 = create_new_node(1);
	for (int i = 0; i < 11; i++) {
		i++;
		add_node_to_end(&head2, i);
	}

	printf("Merge the two following linked lists sorted:\n");
	print_linked_list(head);
	print_linked_list(head2);

	Node *merged_linked_list = merge_sorted_linked_lists(&head, &head2);
	printf("Print sorted merged linked list\n");
	print_linked_list(merged_linked_list);

	// Number of nodes
	int N = 11;
	printf("Create a circular linked list\n");
	Node *circular_linked_list = create_circular_linked_list(N);
	printf("Print the circular linked list\n");
	print_circular_linked_list(circular_linked_list);

	printf("Create a temporary linked list\n");
	Node *temp = create_new_node(1);
	for (int i = 0; i < 11; i++) {
		i++;
		add_node_to_end(&head2, i);
	}

	printf("Checking if list ic circular linked list or not.\nAssuming node values are different\n");
	bool x = is_circular_linked_list(circular_linked_list);
	fputs(x ? "circular_linked_list : true" : "circular_linked_list : false", stdout);
	printf("\n");
	x = is_circular_linked_list(temp);
	fputs(x ? "temp : true" : "temp : false", stdout);
	printf("\n");

	return 0;
}
