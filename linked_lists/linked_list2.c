#include <stdio.h>
#include <stdlib.h>

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

void 
*print_linked_list(Node *head) {
	Node *tmp = head;
	while (tmp != NULL) {
		printf("%d - ", tmp->data);
		tmp = tmp->next;
	}
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

int main(int argc, char *argv[]) {

	Node *head = NULL;

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

	return 0;
}
