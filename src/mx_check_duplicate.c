#include "../inc/pathfinder.h"

bool mx_list_has_bridge(t_list* list, t_bridge* key) {
    t_list* tmp = list;

	while(tmp) {
		t_bridge* bridge = (t_bridge*)tmp->data;
		if(mx_strcmp(key->left, bridge->left) == 0 && mx_strcmp(key->right, bridge->right) == 0) {
			return true;
		}
		tmp = tmp->next;
	}

    return false;
}

bool mx_check_duplicates(t_list* list) {
	t_list* tmp = list;

	while(tmp) {
		t_bridge* key = (t_bridge*)tmp->data;
        if(mx_list_has_bridge(tmp->next, key)) {
            return true;
        }
        tmp = tmp->next;
	}

	return false;
}
