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
			cout << "add empty" << endl;
			current_position_X = new_cus;
			current_position_X->next = current_position_X;
			current_position_X->prev = current_position_X;
			customer_in_restaurant++;
		}
		void add_Clockwise_current_position_X(customer* new_cus)
		{
			cout << "add clockwise" << endl;
			new_cus->next = current_position_X->next;
			new_cus->prev = current_position_X;
			current_position_X->next->prev = new_cus;
			current_position_X->next = new_cus;
			current_position_X = new_cus;
			customer_in_restaurant++;
		}
		void add_antiClockwise_current_position_X(customer* new_cus)
		{
			cout << "add anticlockwise" << endl;
			new_cus->prev = current_position_X->prev;
			new_cus->next = current_position_X;
			current_position_X->prev->next = new_cus;
			current_position_X->prev = new_cus;
			current_position_X = new_cus;
			customer_in_restaurant++;
		}
		void add_waiting_queue(customer* new_cus)
		{
			cout << "add waiting queue" << endl;
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
					ID = -999;
					return;
				}
				ID = stoi(temp);
				//cout << temp << endl;
			}
			else if (order == add_ID)
			{
				if (ID == -999)
				{
					return;
				}
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
		void swap_negative()
		{

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
				//int ID = 0;
				//ID_manuver(scanner, remove_ID, ID);
				scanner->print();
				scanner = scanner->next;
			}
		}
		/* ****************** End Print List ****************** */

		void RED(string name, int energy)
		{
			timer_ID++;
			string timer_ID_str = to_string(timer_ID);
			//cout << "function access successfully" << endl;
			//cout << name << " " << energy << endl;
			customer *new_cus = new customer (name, energy, nullptr, nullptr);
			//cout << MAXSIZE << endl;
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

			new_cus->name = new_cus->name + "_" + timer_ID_str;
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
			new_cus->print();
			//cout << "customer in restaurant: " << customer_in_restaurant << endl;
			//cout << "customer in queue: " << customer_in_queue << endl;
		}
		void BLUE(int num)
		{
			cout << "blue "<< num << endl;
			if (num >= MAXSIZE)
			{
				while (current_position_X != NULL)
				{
					remove_customer();
				}
			}
		}
		void PURPLE()
		{
			cout << "purple"<< endl;
		}
		void REVERSAL()
		{
			cout << "reversal" << endl;
		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;
		}
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;
		}
		void LIGHT(int num)
		{
			cout << "light " << num << endl;
			cout << "Customer list" << endl;
			bool pos = true;
			if (num > 0)
			{
				cout << "******************" << endl;
				print_restaurant(pos);
			}
			else if (num < 0)
			{
				cout << "******************" << endl;
				print_restaurant(!pos);
			}
			else
			{
				cout << "******************" << endl;
				print_waiting_queue();
			}
		}
};