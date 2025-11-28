#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include "criminal.h"
#include "case.h"
#include "graph.h"
#include "history.h"
#include "file_handling.h"

// Global data structures
extern CriminalList criminals;
extern CaseQueue cases;
extern Graph criminal_network;

// Main window function
void start_gui(int argc, char *argv[]);

// Main window
void show_main_window();

// Criminal management
void show_criminal_window();
void refresh_criminal_list(GtkWidget *treeview);
void show_add_criminal_dialog(GtkWidget *parent);
void show_add_multiple_criminals_dialog(GtkWidget *parent);
void show_search_criminal_dialog(GtkWidget *parent);
void show_update_criminal_dialog(GtkWidget *parent);
void show_delete_criminal_dialog(GtkWidget *parent);

// Case management
void show_case_window();
void refresh_case_list(GtkWidget *treeview);
void show_add_case_dialog(GtkWidget *parent);
void show_add_multiple_cases_dialog(GtkWidget *parent);
void show_dequeue_case_dialog(GtkWidget *parent);
void show_peek_case_dialog(GtkWidget *parent);
void show_urgent_cases_dialog(GtkWidget *parent);

// Network management
void show_network_window();
void refresh_network_list(GtkWidget *treeview);
void show_add_connection_dialog(GtkWidget *parent);

// History viewing
void show_criminal_history_dialog(GtkWidget *parent);
void show_case_history_dialog(GtkWidget *parent);
void show_change_log_window();

#endif // GUI_H

