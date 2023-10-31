#include "main.h"

class imp_res : public Restaurant
{
	public:	
		imp_res() {};

		/* ****************** Begin Custom Extra Variable ****************** */
		int customer_in_restaurant = 0;
		int customer_in_queue = 0;
		int time_enter = 0;
		customer* current_position_X = NULL;
		customer* scanning_pointer = NULL;
		customer* waiting_queue_head = NULL;
		customer* waiting_queue_tail = NULL;
		const string restaurant_table = "table list";
		const string restaurant_queue = "queue list";
		int timer_ID = 0;
		string add_ID = "Add ID";
		string remove_ID = "Remove ID";
		string positive = "Positive";
		string negative = "Negative";
		/* ****************** End Custom Extra Variable ****************** */

		/* ****************** Begin Custom Extra Function ****************** */
		//------------------ Check Num ------------------//
		bool is_restaurant_empty()
		{
			if (customer_in_restaurant >= 0 && customer_in_restaurant < MAXSIZE/2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool is_restaurant_half_full()
		{
			if (customer_in_restaurant >= MAXSIZE/2 && customer_in_restaurant < MAXSIZE)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool is_restaurant_full()
		{
			if (customer_in_restaurant == MAXSIZE)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool is_waiting_queue_full()
		{
			if (customer_in_queue == MAXSIZE)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//------------------ Add Node ------------------//
		void add_empty(customer* new_cus)
		{
			//cout << "add empty" << endl;
			current_position_X = new_cus;
			current_position_X->next = current_position_X;
			current_position_X->prev = current_position_X;
			customer_in_restaurant++;
		}
		void add_Clockwise_current_position_X(customer* new_cus)
		{
			//cout << "add clockwise" << endl;
			new_cus->next = current_position_X->next;
			new_cus->prev = current_position_X;
			current_position_X->next->prev = new_cus;
			current_position_X->next = new_cus;
			current_position_X = new_cus;
			customer_in_restaurant++;
		}
		void add_antiClockwise_current_position_X(customer* new_cus)
		{
			//cout << "add anticlockwise" << endl;
			new_cus->prev = current_position_X->prev;
			new_cus->next = current_position_X;
			current_position_X->prev->next = new_cus;
			current_position_X->prev = new_cus;
			current_position_X = new_cus;
			customer_in_restaurant++;
		}
		void add_waiting_queue(customer* new_cus)
		{
			//cout << "add waiting queue" << endl;
			new_cus->prev = new_cus;
			new_cus->next = new_cus;
			if (waiting_queue_head == NULL)
			{
				waiting_queue_head = new_cus;
				waiting_queue_tail = new_cus;
			}
			else
			{
				waiting_queue_head->prev = new_cus;
				waiting_queue_tail->next = new_cus;
				new_cus->next = waiting_queue_head;
				new_cus->prev = waiting_queue_tail;
				waiting_queue_tail = new_cus;
			}
			customer_in_queue++;
		}
		//------------------ Remove Node ------------------//
		void remove_customer()
		{
			if (current_position_X == NULL)
			{
				return;
			}
			customer* next_cus = current_position_X->next;
			customer* prev_cus = current_position_X->prev;
			customer* curr_cus = current_position_X;
			if (customer_in_restaurant == 1)
			{
				current_position_X = NULL;
			}
			else
			{
				if (curr_cus->energy > 0)
				{
					next_cus->prev = prev_cus;
					prev_cus->next = next_cus;
					current_position_X = next_cus;
				}
				else if (curr_cus->energy < 0)
				{
					next_cus->prev = prev_cus;
					prev_cus->next = next_cus;
					current_position_X = prev_cus;
				}
			}
			customer_in_restaurant--;
			delete curr_cus;
		}
		void remove_customer_from_queue()
		{
			if (waiting_queue_head == NULL)
			{
				return;
			}
			customer* remove_cus = waiting_queue_head;
			if (customer_in_queue == 1)
			{
				waiting_queue_head = waiting_queue_tail = NULL;
			}
			else
			{
				waiting_queue_tail->next = waiting_queue_head->next;
				waiting_queue_head->next->prev = waiting_queue_tail;
				waiting_queue_head = waiting_queue_head->next;
			}
			customer_in_queue--;
			delete remove_cus;
		}
		//------------------ ID Manuver ------------------//
		void ID_manuver(customer* current_cus, string order, int& ID)
		{
			if (order == remove_ID)
			{
				string temp = "";
				string temp_name = current_cus->name;
				for (int i = 0; i < (int)temp_name.size(); i++)
				{
					if (temp_name[i] != '_')
					{
						temp = temp + temp_name[i];
					}
					if (temp_name[i] == '_')
					{
						current_cus->name = temp;
						temp = "";
					}
				}
				if (temp == current_cus->name)
				{
					return;
				}
				ID = stoi(temp);
				//cout << temp << endl;
			}
			else if (order == add_ID)
			{
				string str_ID = to_string(ID);
				current_cus->name = current_cus->name + "_" + str_ID;
			}
		}
		int get_customer_ID(customer* current_cus)
		{
			int res_ID = 0;
			ID_manuver(current_cus, remove_ID, res_ID);
			ID_manuver(current_cus, add_ID, res_ID);
			return res_ID;
		}
		int get_smallest_ID()
		{
			int ID = 0;
			int min_ID = INT8_MAX;
			customer* current_cus = current_position_X;
			for (int i = 0; i < customer_in_restaurant; i++)
			{
				ID = get_customer_ID(current_cus);
				if (ID < min_ID)
				{
					min_ID = ID;
				}
				current_cus = current_cus->next;
			}
			return min_ID;
		}
		int get_largest_ID()
		{
			int ID = 0;
			int max_ID = INT8_MIN;
			customer* current_cus = current_position_X;
			for (int i = 0; i < customer_in_restaurant; i++)
			{
				ID = get_customer_ID(current_cus);
				if (ID > max_ID)
				{
					max_ID = ID;
				}
				current_cus = current_cus->next;
			}
			return max_ID;
		}
		void reduce_ID(int max_ID)
		{
			int ID = 0;
			customer* scanner = current_position_X;
			for (int i = 0; i < customer_in_restaurant; i++)
			{
				ID_manuver(scanner, remove_ID, ID);
				ID = ID - max_ID;
				ID_manuver(scanner, add_ID, ID);
				scanner = scanner->next;
			}
		}
		customer* search_customer_ID(int ID)
		{
			customer* search_cus = current_position_X;
			for (int i = 0; i < customer_in_restaurant; i++)
			{
				int search_ID = get_customer_ID(search_cus);
				if (search_ID == ID)
				{
					return search_cus;
				}
				search_cus = search_cus->next;
			}
			return current_position_X;
		}
		int get_largest_ID_queue()
		{
			int ID = 0;
			int max_ID = INT8_MIN;
			customer* current_cus = waiting_queue_head;
			for (int i = 0; i < customer_in_queue; i++)
			{
				ID = get_customer_ID(current_cus);
				if (ID > max_ID)
				{
					max_ID = ID;
				}
				current_cus = current_cus->next;
			}
			return max_ID;
		}
		void reduce_ID_queue(int max_ID)
		{
			int ID = 0;
			customer* scanner = waiting_queue_head;
			for (int i = 0; i < customer_in_queue; i++)
			{
				ID_manuver(scanner, remove_ID, ID);
				ID = ID - max_ID;
				ID_manuver(scanner, add_ID, ID);
				scanner = scanner->next;
			}
		}
		//------------------ Empty Strategy ------------------//
		void empty_restaurant_strategy(customer* new_cus)
		{
			if (current_position_X == NULL)
			{
				add_empty(new_cus);
				return;
			}
			if (new_cus->energy >= current_position_X->energy)
			{
				add_Clockwise_current_position_X(new_cus);
			}
			else
			{
				add_antiClockwise_current_position_X(new_cus);
			}
		}
		//------------------ Half-full Strategy ------------------//
		int max_abs_val_idx(customer* new_cus)
		{
			customer* scanner_ptr = current_position_X->next;
			int max_abs = abs(new_cus->energy - current_position_X->energy);
			int idx = 1;
			int max_idx = 1;
			while (scanner_ptr != current_position_X)
			{
				idx++;
				int current_abs = abs(new_cus->energy - scanner_ptr->energy);
				if (current_abs > max_abs)
				{
					max_abs = current_abs;
					max_idx = idx;
				}
				scanner_ptr = scanner_ptr->next;
			}
			return max_idx;
		}
		void half_full_strategy(customer* new_cus)
		{
			int max_idx = max_abs_val_idx(new_cus);
			int idx = 1;
			//cout << max_idx << endl;
			while (idx != max_idx)
			{
				idx++;
				current_position_X = current_position_X->next;
			}
			int res = new_cus->energy - current_position_X->energy;
			if (res < 0)
			{
				add_Clockwise_current_position_X(new_cus);
			}
			else
			{
				add_antiClockwise_current_position_X(new_cus);
			}
		}
		//------------------ Scan Dup ------------------//
		bool Ore_Koso_Only_One(customer* new_cus, string scanning_list)
		{
			if (scanning_list == restaurant_table)
			{
				if (current_position_X == NULL)
				{
					return true;
				}
				customer* scan_ptr = current_position_X->next;
				int new_cus_ID = 0;
				int initial_ID = 0;
				ID_manuver(current_position_X, remove_ID, initial_ID);
				ID_manuver(new_cus, remove_ID, new_cus_ID);
				if (current_position_X->name == new_cus->name)
				{
					ID_manuver(current_position_X, add_ID, initial_ID);
					ID_manuver(new_cus, add_ID, new_cus_ID);
					return false;
				}
				else
				{
					ID_manuver(current_position_X, add_ID, initial_ID);
					while (scan_ptr != current_position_X)
					{
						int current_scanner_ID = 0;
						ID_manuver(scan_ptr, remove_ID, current_scanner_ID);
						if (scan_ptr->name == new_cus->name)
						{
							ID_manuver(scan_ptr, add_ID, current_scanner_ID);
							ID_manuver(new_cus, add_ID, new_cus_ID);
							return false;
						}
						ID_manuver(scan_ptr, add_ID, current_scanner_ID);
						scan_ptr = scan_ptr->next;
					}
					ID_manuver(new_cus, add_ID, new_cus_ID);
				}
			}
			else if(scanning_list == restaurant_queue)
			{
				if (waiting_queue_head == NULL)
				{
					return true;
				}
				customer* scan_ptr = waiting_queue_head->next;
				int new_cus_ID = 0;
				int initial_ID = 0;
				ID_manuver(waiting_queue_head, remove_ID, initial_ID);
				ID_manuver(new_cus, remove_ID, new_cus_ID);
				if (waiting_queue_head->name == new_cus->name)
				{
					ID_manuver(waiting_queue_head, add_ID, initial_ID);
					ID_manuver(new_cus, add_ID, new_cus_ID);
					return false;
				}
				else
				{
					ID_manuver(waiting_queue_head, add_ID, initial_ID);
					while (scan_ptr != waiting_queue_head)
					{
						int current_scanner_ID = 0;
						ID_manuver(scan_ptr, remove_ID, current_scanner_ID);
						if (scan_ptr->name == new_cus->name)
						{
							ID_manuver(scan_ptr, add_ID, current_scanner_ID);
							ID_manuver(new_cus, add_ID, new_cus_ID);
							return false;
						}
						ID_manuver(scan_ptr, add_ID, current_scanner_ID);
						scan_ptr = scan_ptr->next;
					}
					ID_manuver(new_cus, add_ID, new_cus_ID);
				}
			}
			return true;
		}
		//------------------ Check num of Element ------------------//
		int num_of_element(string state)
		{
			int num = 0;
			customer* scanner = current_position_X;
			if (state == positive)
			{
				for (int i = 0; i < customer_in_restaurant; i++)
				{
					if (scanner->energy > 0)
					{
						num++;
					}
					scanner = scanner->next;
				}
			}
			else if (state == negative)
			{
				for (int i = 0; i < customer_in_restaurant; i++)
				{
					if (scanner->energy < 0)
					{
						num++;
					}
					scanner = scanner->next;
				}
			}
			return num;
		}
		//------------------ Swap ------------------//
		void swap_node(customer* cus_1, customer* cus_2)
		{
			customer* cus_1_prev = cus_1->prev;
			customer* cus_1_next = cus_1->next;
			customer* cus_2_prev = cus_2->prev;
			customer* cus_2_next = cus_2->next;

			cus_1->prev = cus_2_prev;
			cus_1->next = cus_2_next;
			cus_2_prev->next = cus_1;
			cus_2_next->prev = cus_1;

			cus_2->prev = cus_1_prev;
			cus_2->next = cus_1_next;
			cus_1_prev->next = cus_2;
			cus_1_next->prev = cus_2;
		}
		void swap_node_close(customer* cus_1, customer* cus_2)
		{
			customer* cus_1_prev = cus_1->prev;
			customer* cus_2_next = cus_2->next;

			cus_1->prev = cus_2;
			cus_1->next = cus_2_next;
			cus_1_prev->next = cus_2;

			cus_2->next = cus_1;
			cus_2->prev = cus_1_prev;
			cus_2_next->prev = cus_1;
		}
		void swap(int num, string state)
		{
			customer* forward = current_position_X;
			customer* backward = current_position_X->prev;
			for (int i = 0; i < num / 2; i++)
			{
				if (state == positive)
				{
					int distance = 0;
					while (forward->energy < 0)
					{
						forward = forward->next;
						distance++;
					}
					while (backward->energy < 0)
					{
						backward = backward->prev;
						distance++;
					}
					if (distance == 0)
					{
						swap_node_close(forward, backward);
					}
					else
					{
						swap_node(forward, backward);
					}
				}
				else if(state == negative)
				{
					int distance = 0;
					while (forward->energy > 0)
					{
						forward = forward->next;
						distance++;
					}
					while (backward->energy > 0)
					{
						backward = backward->prev;
						distance++;
					}
					if (distance == 0)
					{
						swap_node_close(forward, backward);
					}
					else
					{
						swap_node(forward, backward);
					}
				}
				forward = forward->next;
				backward = backward->prev;
			}
		}
		//------------------ Sort ------------------//
		int max_abs_energy()
		{
			int max_energy = INT8_MIN;
			customer* scanner = waiting_queue_head;
			for (int i = 0; i < customer_in_queue; i++)
			{
				if (abs(scanner->energy) > max_energy)
				{
					max_energy = abs(scanner->energy);
				}
				scanner = scanner->next;
			}
			return max_energy;
		}
		customer* max_abs_energy_node()
		{
			int max_energy = max_abs_energy();
			customer* scanner = waiting_queue_head;
			for (int i = 0; i < customer_in_queue; i++)
			{
				if (abs(scanner->energy) == max_energy)
				{
					break;
				}
				scanner = scanner->prev;
			}
			return scanner;
		}
		int from_head_to_highest_abs_energy()
		{
			int counter = 1;
			customer* scanner = waiting_queue_head;
			customer* end = max_abs_energy_node();
			while (scanner != end)
			{
				counter++;
				scanner = scanner->next;
			}
			return counter;
		}
		void shellSort(int n, customer* end_node)
		{
			for (int gap = n/2; gap > 0; gap /= 2)
			{
				//cout << "gap: " << gap << endl;
				customer* cus_1 = waiting_queue_head;
				customer* cus_2 = waiting_queue_head;
				int counter = gap;
				while (counter > 0)
				{
					cus_2 = cus_2->next;
					counter--;
				}
				int loop_count = 0;
				for (int i = gap; i < n; i++)
				{
					customer* cus_1_next = cus_1->next;
					customer* cus_2_next = cus_2->next;
					//cout << "cus 1: " << cus_1->name << " " << cus_1->energy << endl;
					//cout << "cus 2: " << cus_2->name << " " << cus_2->energy << endl;
					if (abs(cus_1->energy) > abs(cus_2->energy) && gap > 1)
					{
						//cout << "cus 1: " << cus_1->name << " " << cus_1->energy << endl;
						//cout << "cus 2: " << cus_2->name << " " << cus_2->energy << endl;
						if (cus_1 == waiting_queue_head)
						{
							waiting_queue_head = cus_2;
						}
						swap_node(cus_1, cus_2);
					}
					else if (abs(cus_1->energy) > abs(cus_2->energy) && gap == 1)
					{
						//cout << "cus 1: " << cus_1->name << " " << cus_1->energy << endl;
						//cout << "cus 2: " << cus_2->name << " " << cus_2->energy << endl;
						if (cus_1 == waiting_queue_head)
						{
							waiting_queue_head = cus_2;
						}
						swap_node_close(cus_1, cus_2);
						cus_1_next = cus_1;
					}
					else if (abs(cus_1->energy) == abs(cus_2->energy) && gap > 1)
					{
						int cus_1_ID = get_customer_ID(cus_1);
						int cus_2_ID = get_customer_ID(cus_2);
						if (cus_1_ID > cus_2_ID)
						{
							if (cus_1 == waiting_queue_head)
							{
								waiting_queue_head = cus_2;
							}
							swap_node(cus_1, cus_2);
						}
					}
					else if (abs(cus_1->energy) == abs(cus_2->energy) && gap == 1)
					{
						int cus_1_ID = get_customer_ID(cus_1);
						int cus_2_ID = get_customer_ID(cus_2);
						if (cus_1_ID > cus_2_ID)
						{
							if (cus_1 == waiting_queue_head)
							{
								waiting_queue_head = cus_2;
							}
							swap_node_close(cus_1, cus_2);
							cus_1_next = cus_1;
						}
					}
					//cout << "cus 1: " << cus_1->name << " " << cus_1->energy << endl;
					//cout << "cus 2: " << cus_2->name << " " << cus_2->energy << endl;
					cus_1 = cus_1_next;
					cus_2 = cus_2_next;
					//cout << "******************" << endl;
					//print_waiting_queue();
					//cout << "******************" << endl;
				}
			}
		}
		/* ****************** END Custom Extra Function ****************** */

		/* ****************** Begin Print List ****************** */
		void print_restaurant(bool pos)
		{
			if (current_position_X == NULL)
			{
				return;
			}
			customer* scanner = current_position_X;
			if (current_position_X->energy < 0)
			{
				pos = false;
			}
			for (int i = 0; i < customer_in_restaurant; i++)
			{
				int ID = 0;
				ID_manuver(scanner, remove_ID, ID);
				scanner->print();
				if (pos)
				{
					scanner = scanner->next;
				}
				else
				{
					scanner = scanner->prev;
				}
			}
		}
		void print_waiting_queue()
		{
			if (waiting_queue_head == NULL)
			{
				return;
			}
			customer* scanner = waiting_queue_head;
			for (int i = 0; i < customer_in_queue; i++)
			{
				int ID = 0;
				ID_manuver(scanner, remove_ID, ID);
				scanner->print();
				scanner = scanner->next;
			}
		}
		/* ****************** End Print List ****************** */

		void RED(string name, int energy)
		{
			if (energy == 0)
			{
				return;
			}
			//cout << "red" << " " << name << " " << energy << endl;
			//reset timer and reduce ID for customer that came before
			if (timer_ID == INT8_MAX)
			{
				if (current_position_X != NULL)
				{
					int max_ID = get_largest_ID();
					reduce_ID(max_ID);
				}
				if (waiting_queue_head != NULL)
				{
					int max_ID_queue = get_largest_ID_queue();
					reduce_ID_queue(max_ID_queue);
				}
				timer_ID = 0;
			}
			timer_ID++;
			string timer_ID_str = to_string(timer_ID);
			//cout << "function access successfully" << endl;
			//cout << name << " " << energy << endl;
			customer *new_cus = new customer (name, energy, nullptr, nullptr);
			//cout << MAXSIZE << endl;
			if (!is_restaurant_full())
			{
				
			}
			//Check Duplicate
			new_cus->name = new_cus->name + "_" + timer_ID_str;
			if (!Ore_Koso_Only_One(new_cus, restaurant_queue))
			{
				//cout << "Match" << endl;
				return;
			}
			if (!Ore_Koso_Only_One(new_cus, restaurant_table))
			{
				//cout << "Match" << endl;
				return;
			}
			//Add customer
			if (is_restaurant_empty())
			{
				empty_restaurant_strategy(new_cus);
			}
			else if (is_restaurant_half_full())
			{
				half_full_strategy(new_cus);
			}
			else if(is_restaurant_full())
			{
				if (customer_in_queue < MAXSIZE)
				{
					add_waiting_queue(new_cus);
				}
			}
			//new_cus->print();
			//cout << "customer in restaurant: " << customer_in_restaurant << endl;
			//cout << "customer in queue: " << customer_in_queue << endl;
		}
		void BLUE(int num)
		{
			//cout << "------------------" << endl;
			//cout << "blue "<< num << endl;
			if (num >= MAXSIZE)
			{
				while (current_position_X != NULL)
				{
					remove_customer();
				}
			}
			else
			{
				//cout << "customer in restaurant before: " << customer_in_restaurant << endl;
				//cout << "customer in queue before: " << customer_in_queue << endl;
				for (int i = 0; i < num; i++)
				{
					int ID = get_smallest_ID();
					customer* remove_cus = search_customer_ID(ID);
					//cout << "ID: " << ID << endl;
					//cout << "Customer: " << remove_cus->name << " " << remove_cus->energy << endl;
					current_position_X = remove_cus;
					remove_customer();
					//cout << "current X: " << current_position_X->name << " " << current_position_X->energy << endl;
				}
				//cout << "customer in restaurant mid: " << customer_in_restaurant << endl;
				//cout << "customer in queue mid: " << customer_in_queue << endl;
				while (customer_in_queue > 0 && customer_in_restaurant < MAXSIZE)
				{
					//cout << "queue head: " << waiting_queue_head->name << " " << waiting_queue_head->energy << endl;
					int ID = 0;
					ID_manuver(waiting_queue_head, remove_ID, ID);
					//cout << "queue head: " << waiting_queue_head->name << " " << waiting_queue_head->energy << endl;
					string name = waiting_queue_head->name;
					int energy = waiting_queue_head->energy;
					remove_customer_from_queue();
					RED(name, energy);
					//cout << "customer in restaurant after: " << customer_in_restaurant << endl;
					//cout << "customer in queue after: " << customer_in_queue << endl;
				}
			}
		}
		void PURPLE()
		{
			//cout << "purple"<< endl;
			if (waiting_queue_head == NULL)
			{
				return;
			}
			int size = from_head_to_highest_abs_energy();
			//cout << "size: " << size << endl;
			customer* end_node = max_abs_energy_node();
			shellSort(size,end_node);
			//cout << "purple---------------------------------------------------------------------" << endl;
		}
		void REVERSAL()
		{
			//cout << "reversal" << endl;
			int energy_state = current_position_X->energy;
			int num = 0;
			if (energy_state > 0)
			{
				num = num_of_element(positive);
				swap(num, positive);
			}
			else if (energy_state < 0)
			{
				num = num_of_element(negative);
				swap(num, negative);
			}
		}
		void UNLIMITED_VOID()
		{
			//cout << "unlimited_void" << endl;
			// I have no idea :) 
		}
		void DOMAIN_EXPANSION()
		{
			//cout << "domain_expansion" << endl;
		}
		void LIGHT(int num)
		{
			//cout << "light " << num << endl;
			//cout << "Customer list" << endl;
			bool pos = true;
			if (num > 0)
			{
				//cout << "******************" << endl;
				print_restaurant(pos);
			}
			else if (num < 0)
			{
				//cout << "******************" << endl;
				print_restaurant(!pos);
			}
			else
			{
				//cout << "******************" << endl;
				print_waiting_queue();
			}
		}
};