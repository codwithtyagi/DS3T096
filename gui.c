#include <gtk/gtk.h>
#include "gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* glib.h is included by gtk/gtk.h, no need to include separately */

// Global data structures (defined in main_gui.c)
extern CriminalList criminals;
extern CaseQueue cases;
extern Graph criminal_network;

// Internal callback functions (forward declarations)
static void on_save_clicked(GtkWidget *widget, gpointer data);
static void on_criminal_manage_clicked(GtkWidget *widget, gpointer data);
static void on_case_manage_clicked(GtkWidget *widget, gpointer data);
static void on_network_manage_clicked(GtkWidget *widget, gpointer data);
static void on_criminal_history_clicked(GtkWidget *widget, gpointer data);
static void on_case_history_clicked(GtkWidget *widget, gpointer data);
static void on_change_log_clicked(GtkWidget *widget, gpointer data);
static void on_main_window_destroy(GtkWidget *widget, gpointer data);
static void on_refresh_criminal_clicked(GtkWidget *widget, gpointer data);
static void on_refresh_case_clicked(GtkWidget *widget, gpointer data);
static void on_refresh_network_clicked(GtkWidget *widget, gpointer data);

// Apply CSS styling
static void apply_css_styling(GtkWidget *widget) {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    const gchar *css_style = 
        "window {"
        "    background: linear-gradient(135deg, #667eea 0%, #764ba2 50%, #667eea 100%);"
        "}"
        ".dialog-window {"
        "    background: linear-gradient(to bottom, #34495e, #2c3e50);"
        "    border-radius: 12px;"
        "}"
        ".main-title {"
        "    color: #ffffff;"
        "    font-size: 32px;"
        "    font-weight: 900;"
        "    text-shadow: 0 0 20px rgba(255, 255, 255, 0.5), 3px 3px 6px rgba(0, 0, 0, 0.7);"
        "    padding: 25px;"
        "    letter-spacing: 2px;"
        "}"
        "button {"
        "    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);"
        "    color: white;"
        "    border: none;"
        "    border-radius: 12px;"
        "    padding: 14px 28px;"
        "    font-size: 15px;"
        "    font-weight: 700;"
        "    box-shadow: 0 8px 16px rgba(0, 0, 0, 0.4), 0 0 20px rgba(102, 126, 234, 0.3);"
        "    transition: all 0.4s cubic-bezier(0.4, 0, 0.2, 1);"
        "    letter-spacing: 0.5px;"
        "    outline: none;"
        "}"
        "button:hover {"
        "    background: linear-gradient(135deg, #764ba2 0%, #667eea 100%);"
        "    box-shadow: 0 12px 24px rgba(0, 0, 0, 0.5), 0 0 30px rgba(118, 75, 162, 0.5);"
        "    scale: 1.05;"
        "}"
        "button:active {"
        "    background: linear-gradient(135deg, #5a67d8 0%, #667eea 100%);"
        "    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.3);"
        "    scale: 0.98;"
        "}"
        ".criminal-btn {"
        "    background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%);"
        "    box-shadow: 0 8px 16px rgba(0, 0, 0, 0.4), 0 0 20px rgba(245, 87, 108, 0.3);"
        "}"
        ".criminal-btn:hover {"
        "    background: linear-gradient(135deg, #f5576c 0%, #f093fb 100%);"
        "    box-shadow: 0 12px 24px rgba(0, 0, 0, 0.5), 0 0 30px rgba(240, 147, 251, 0.5);"
        "}"
        ".case-btn {"
        "    background: linear-gradient(135deg, #ffecd2 0%, #fcb69f 100%);"
        "    color: #2c3e50;"
        "    box-shadow: 0 8px 16px rgba(0, 0, 0, 0.4), 0 0 20px rgba(252, 182, 159, 0.3);"
        "}"
        ".case-btn:hover {"
        "    background: linear-gradient(135deg, #fcb69f 0%, #ffecd2 100%);"
        "    box-shadow: 0 12px 24px rgba(0, 0, 0, 0.5), 0 0 30px rgba(255, 236, 210, 0.5);"
        "}"
        ".network-btn {"
        "    background: linear-gradient(135deg, #a8edea 0%, #fed6e3 100%);"
        "    color: #2c3e50;"
        "    box-shadow: 0 8px 16px rgba(0, 0, 0, 0.4), 0 0 20px rgba(168, 237, 234, 0.3);"
        "}"
        ".network-btn:hover {"
        "    background: linear-gradient(135deg, #fed6e3 0%, #a8edea 100%);"
        "    box-shadow: 0 12px 24px rgba(0, 0, 0, 0.5), 0 0 30px rgba(254, 214, 227, 0.5);"
        "}"
        ".history-btn {"
        "    background: linear-gradient(135deg, #84fab0 0%, #8fd3f4 100%);"
        "    color: #2c3e50;"
        "    box-shadow: 0 8px 16px rgba(0, 0, 0, 0.4), 0 0 20px rgba(132, 250, 176, 0.3);"
        "}"
        ".history-btn:hover {"
        "    background: linear-gradient(135deg, #8fd3f4 0%, #84fab0 100%);"
        "    box-shadow: 0 12px 24px rgba(0, 0, 0, 0.5), 0 0 30px rgba(143, 211, 244, 0.5);"
        "}"
        ".save-btn {"
        "    background: linear-gradient(135deg, #d4fc79 0%, #96e6a1 100%);"
        "    color: #2c3e50;"
        "    box-shadow: 0 8px 16px rgba(0, 0, 0, 0.4), 0 0 20px rgba(212, 252, 121, 0.3);"
        "}"
        ".save-btn:hover {"
        "    background: linear-gradient(135deg, #96e6a1 0%, #d4fc79 100%);"
        "    box-shadow: 0 12px 24px rgba(0, 0, 0, 0.5), 0 0 30px rgba(150, 230, 161, 0.5);"
        "}"
        ".separator {"
        "    background: linear-gradient(to right, transparent, rgba(255, 255, 255, 0.4), transparent);"
        "    border: none;"
        "    margin: 20px 0;"
        "    min-height: 2px;"
        "    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);"
        "}"
        "label {"
        "    color: #ecf0f1;"
        "    font-size: 14px;"
        "    font-weight: 500;"
        "    padding: 4px;"
        "}"
        "entry {"
        "    background: rgba(255, 255, 255, 0.95);"
        "    color: #2c3e50;"
        "    border: 2px solid rgba(102, 126, 234, 0.3);"
        "    border-radius: 8px;"
        "    padding: 10px 14px;"
        "    font-size: 14px;"
        "    box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);"
        "    transition: all 0.3s ease;"
        "}"
        "entry:focus {"
        "    border: 2px solid #667eea;"
        "    box-shadow: 0 4px 12px rgba(102, 126, 234, 0.4), 0 0 0 3px rgba(102, 126, 234, 0.1);"
        "    background: white;"
        "}"
        "textview {"
        "    background: rgba(255, 255, 255, 0.95);"
        "    color: #2c3e50;"
        "    border: 2px solid rgba(102, 126, 234, 0.3);"
        "    border-radius: 8px;"
        "    padding: 10px;"
        "    font-size: 13px;"
        "    box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);"
        "}"
        "textview text {"
        "    background: transparent;"
        "    color: #2c3e50;"
        "}"
        "treeview {"
        "    background: rgba(255, 255, 255, 0.98);"
        "    color: #2c3e50;"
        "    border-radius: 8px;"
        "    padding: 5px;"
        "}"
        "treeview:selected {"
        "    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);"
        "    color: white;"
        "}"
        "treeview:hover {"
        "    background: rgba(255, 255, 255, 1);"
        "}"
        "scrolledwindow {"
        "    background: rgba(255, 255, 255, 0.1);"
        "    border-radius: 10px;"
        "    padding: 5px;"
        "}"
        "dialog {"
        "    background: linear-gradient(to bottom, #34495e, #2c3e50);"
        "    border-radius: 15px;"
        "    box-shadow: 0 20px 60px rgba(0, 0, 0, 0.5);"
        "}"
        ".card {"
        "    background: rgba(255, 255, 255, 0.15);"
        "    border-radius: 15px;"
        "    padding: 20px;"
        "    border: 1px solid rgba(255, 255, 255, 0.2);"
        "    box-shadow: 0 8px 32px rgba(0, 0, 0, 0.3);"
        "    backdrop-filter: blur(10px);"
        "}";
    
    gtk_css_provider_load_from_data(css_provider, css_style, -1, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css_provider), 
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(css_provider);
}

// Main window
void show_main_window() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Criminal Management System");
    gtk_window_set_default_size(GTK_WINDOW(window), 650, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(on_main_window_destroy), NULL);

    // Apply CSS styling to window
    apply_css_styling(window);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 30);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Title with styling
    GtkWidget *title = gtk_label_new(NULL);
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_widget_set_name(title, "main-title");
    gtk_label_set_markup(GTK_LABEL(title), 
        "<span size='xx-large' weight='900' foreground='#ffffff'>"
        "🛡️ Criminal Management System 🛡️</span>");
    gtk_box_pack_start(GTK_BOX(vbox), title, FALSE, FALSE, 25);

    // Separator
    GtkWidget *separator1 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_name(separator1, "separator");
    gtk_box_pack_start(GTK_BOX(vbox), separator1, FALSE, FALSE, 10);

    // Main function buttons with enhanced styling
    GtkWidget *criminal_btn = gtk_button_new_with_label("👤 Criminal Management");
    gtk_widget_set_size_request(criminal_btn, 380, 60);
    gtk_widget_set_name(criminal_btn, "criminal-btn");
    g_signal_connect(criminal_btn, "clicked", G_CALLBACK(on_criminal_manage_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), criminal_btn, FALSE, FALSE, 12);

    GtkWidget *case_btn = gtk_button_new_with_label("📋 Case Management");
    gtk_widget_set_size_request(case_btn, 380, 60);
    gtk_widget_set_name(case_btn, "case-btn");
    g_signal_connect(case_btn, "clicked", G_CALLBACK(on_case_manage_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), case_btn, FALSE, FALSE, 12);

    GtkWidget *network_btn = gtk_button_new_with_label("🌐 Criminal Network");
    gtk_widget_set_size_request(network_btn, 380, 60);
    gtk_widget_set_name(network_btn, "network-btn");
    g_signal_connect(network_btn, "clicked", G_CALLBACK(on_network_manage_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), network_btn, FALSE, FALSE, 12);

    // Separator
    GtkWidget *separator2 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_name(separator2, "separator");
    gtk_box_pack_start(GTK_BOX(vbox), separator2, FALSE, FALSE, 10);

    // History and log buttons
    GtkWidget *crim_hist_btn = gtk_button_new_with_label("📜 View Criminal History");
    gtk_widget_set_size_request(crim_hist_btn, 380, 60);
    gtk_widget_set_name(crim_hist_btn, "history-btn");
    g_signal_connect(crim_hist_btn, "clicked", G_CALLBACK(on_criminal_history_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), crim_hist_btn, FALSE, FALSE, 12);

    GtkWidget *case_hist_btn = gtk_button_new_with_label("📜 View Case History");
    gtk_widget_set_size_request(case_hist_btn, 380, 60);
    gtk_widget_set_name(case_hist_btn, "history-btn");
    g_signal_connect(case_hist_btn, "clicked", G_CALLBACK(on_case_history_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), case_hist_btn, FALSE, FALSE, 12);

    GtkWidget *log_btn = gtk_button_new_with_label("📝 View Change Log");
    gtk_widget_set_size_request(log_btn, 380, 60);
    gtk_widget_set_name(log_btn, "history-btn");
    g_signal_connect(log_btn, "clicked", G_CALLBACK(on_change_log_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), log_btn, FALSE, FALSE, 12);

    // Separator
    GtkWidget *separator3 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_name(separator3, "separator");
    gtk_box_pack_start(GTK_BOX(vbox), separator3, FALSE, FALSE, 15);

    // Save button
    GtkWidget *save_btn = gtk_button_new_with_label("💾 Save All Data");
    gtk_widget_set_size_request(save_btn, 380, 60);
    gtk_widget_set_name(save_btn, "save-btn");
    g_signal_connect(save_btn, "clicked", G_CALLBACK(on_save_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), save_btn, FALSE, FALSE, 12);

    gtk_widget_show_all(window);
}

static void on_main_window_destroy(GtkWidget *widget, gpointer data) {
    (void)widget; (void)data;
    savecrim(&criminals);
    savecase(&cases);
    gtk_main_quit();
}

static void on_save_clicked(GtkWidget *widget, gpointer data) {
    (void)data;
    savecrim(&criminals);
    savecase(&cases);
    
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *dialog = gtk_message_dialog_new(GTK_IS_WINDOW(toplevel) ? GTK_WINDOW(toplevel) : NULL,
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "All data saved successfully!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Criminal Management Window
void refresh_criminal_list(GtkWidget *treeview) {
    if (!treeview || !GTK_IS_TREE_VIEW(treeview)) return;
    
    GtkTreeView *tv = GTK_TREE_VIEW(treeview);
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(tv));
    gtk_list_store_clear(store);
    
    CriminalNode *current = criminals.head;
    while (current != NULL) {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                          0, current->data.id,
                          1, current->data.name,
                          2, current->data.age,
                          3, current->data.crime,
                          4, current->data.status,
                          -1);
        current = current->next;
    }
}

void show_criminal_window() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Criminal Management");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 650);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    apply_css_styling(window);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 15);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Title
    GtkWidget *title_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title_label), "<span size='large' weight='bold' foreground='#ecf0f1'>👤 Criminal Management</span>");
    gtk_widget_set_halign(title_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), title_label, FALSE, FALSE, 5);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 8);

    GtkWidget *add_btn = gtk_button_new_with_label("➕ Add Criminal");
    gtk_widget_set_size_request(add_btn, 130, 40);
    g_signal_connect(add_btn, "clicked", G_CALLBACK(show_add_criminal_dialog), window);
    gtk_box_pack_start(GTK_BOX(hbox), add_btn, FALSE, FALSE, 5);

    GtkWidget *add_multiple_btn = gtk_button_new_with_label("➕➕ Add Multiple");
    gtk_widget_set_size_request(add_multiple_btn, 140, 40);
    g_signal_connect(add_multiple_btn, "clicked", G_CALLBACK(show_add_multiple_criminals_dialog), window);
    gtk_box_pack_start(GTK_BOX(hbox), add_multiple_btn, FALSE, FALSE, 5);

    GtkWidget *search_btn = gtk_button_new_with_label("🔍 Search");
    gtk_widget_set_size_request(search_btn, 120, 40);
    g_signal_connect(search_btn, "clicked", G_CALLBACK(show_search_criminal_dialog), window);
    gtk_box_pack_start(GTK_BOX(hbox), search_btn, FALSE, FALSE, 5);

    GtkWidget *update_btn = gtk_button_new_with_label("✏️ Update");
    gtk_widget_set_size_request(update_btn, 120, 40);
    g_signal_connect(update_btn, "clicked", G_CALLBACK(show_update_criminal_dialog), window);
    gtk_box_pack_start(GTK_BOX(hbox), update_btn, FALSE, FALSE, 5);

    GtkWidget *delete_btn = gtk_button_new_with_label("🗑️ Delete");
    gtk_widget_set_size_request(delete_btn, 120, 40);
    gtk_widget_set_name(delete_btn, "criminal-btn");
    g_signal_connect(delete_btn, "clicked", G_CALLBACK(show_delete_criminal_dialog), window);
    gtk_box_pack_start(GTK_BOX(hbox), delete_btn, FALSE, FALSE, 5);

    GtkWidget *refresh_btn = gtk_button_new_with_label("🔄 Refresh");
    gtk_widget_set_size_request(refresh_btn, 120, 40);
    g_object_set_data(G_OBJECT(refresh_btn), "window", window);
    g_signal_connect(refresh_btn, "clicked", G_CALLBACK(on_refresh_criminal_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), refresh_btn, FALSE, FALSE, 5);

    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 0);

    GtkListStore *store = gtk_list_store_new(5, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Age", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Crime", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Status", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    gtk_container_add(GTK_CONTAINER(scrolled), treeview);
    g_object_set_data(G_OBJECT(window), "treeview", treeview);

    refresh_criminal_list(treeview);
    gtk_widget_show_all(window);
}

void show_add_criminal_dialog(GtkWidget *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Add Criminal",
                                                     GTK_WINDOW(parent),
                                                     GTK_DIALOG_MODAL,
                                                     "Cancel", GTK_RESPONSE_CANCEL,
                                                     "Add", GTK_RESPONSE_ACCEPT,
                                                     NULL);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    GtkWidget *entries[5];
    const char *labels[] = {"ID:", "Name:", "Age:", "Crime:", "Status:"};

    for (int i = 0; i < 5; i++) {
        GtkWidget *label = gtk_label_new(labels[i]);
        gtk_widget_set_halign(label, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i, 1, 1);
        entries[i] = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), entries[i], 1, i, 1, 1);
    }

    gtk_container_add(GTK_CONTAINER(content), grid);
    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        int id = atoi(gtk_entry_get_text(GTK_ENTRY(entries[0])));
        const char *name = gtk_entry_get_text(GTK_ENTRY(entries[1]));
        int age = atoi(gtk_entry_get_text(GTK_ENTRY(entries[2])));
        const char *crime = gtk_entry_get_text(GTK_ENTRY(entries[3]));
        const char *status = gtk_entry_get_text(GTK_ENTRY(entries[4]));

        // Check if ID exists
        CriminalNode *current = criminals.head;
        while (current != NULL) {
            if (current->data.id == id) {
                GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                                  GTK_DIALOG_MODAL,
                                                                  GTK_MESSAGE_ERROR,
                                                                  GTK_BUTTONS_OK,
                                                                  "Criminal ID already exists!");
                gtk_dialog_run(GTK_DIALOG(error_dialog));
                gtk_widget_destroy(error_dialog);
                gtk_widget_destroy(dialog);
                return;
            }
            current = current->next;
        }

        CriminalNode *newNode = (CriminalNode*)malloc(sizeof(CriminalNode));
        newNode->data.id = id;
        strncpy(newNode->data.name, name, MAX_NAME_LEN - 1);
        newNode->data.name[MAX_NAME_LEN - 1] = '\0';
        newNode->data.age = age;
        strncpy(newNode->data.crime, crime, MAX_CRIME_LEN - 1);
        newNode->data.crime[MAX_CRIME_LEN - 1] = '\0';
        strncpy(newNode->data.status, status, 19);
        newNode->data.status[19] = '\0';
        newNode->next = NULL;

        if (criminals.head == NULL) {
            criminals.head = newNode;
        } else {
            current = criminals.head;
            while (current->next != NULL) current = current->next;
            current->next = newNode;
        }
        criminals.size++;

        addcrimact(id, "Added new criminal");
        addcrimdet(&newNode->data, "Added new criminal");

        GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                            GTK_DIALOG_MODAL,
                                                            GTK_MESSAGE_INFO,
                                                            GTK_BUTTONS_OK,
                                                            "Criminal added successfully!");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);

        // Refresh the list if parent window exists
        if (parent) {
            GtkWidget *treeview = (GtkWidget*)g_object_get_data(G_OBJECT(parent), "treeview");
            if (treeview) refresh_criminal_list(treeview);
        }
    }
    gtk_widget_destroy(dialog);
}

void show_add_multiple_criminals_dialog(GtkWidget *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Add Multiple Criminals",
                                                     GTK_WINDOW(parent),
                                                     GTK_DIALOG_MODAL,
                                                     "Cancel", GTK_RESPONSE_CANCEL,
                                                     "Add All", GTK_RESPONSE_ACCEPT,
                                                     NULL);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 700, 500);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    gtk_container_add(GTK_CONTAINER(content), vbox);

    // Instructions
    GtkWidget *info_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info_label), 
        "<span font='11'><b>Enter multiple criminals (one per line):</b>\n"
        "Format: <tt>ID|Name|Age|Crime|Status</tt>\n"
        "Example: <tt>101|John Doe|35|Robbery|Active</tt></span>");
    gtk_label_set_line_wrap(GTK_LABEL(info_label), TRUE);
    gtk_widget_set_halign(info_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), info_label, FALSE, FALSE, 5);

    // Text view for batch input
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolled, 650, 350);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 5);

    GtkWidget *textview = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(scrolled), textview);

    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
        GtkTextIter start, end;
        gtk_text_buffer_get_bounds(buffer, &start, &end);
        gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        
        int success_count = 0;
        int fail_count = 0;
        char errors[2000] = "";
        
        // Parse each line
        char *line = strtok(text, "\n");
        while (line != NULL) {
            // Skip empty lines
            while (*line == ' ' || *line == '\t') line++;
            if (*line == '\0' || *line == '\n') {
                line = strtok(NULL, "\n");
                continue;
            }
            
            // Parse format: ID|Name|Age|Crime|Status
            int id, age;
            char name[50], crime[100], status[20];
            if (sscanf(line, "%d|%49[^|]|%d|%99[^|]|%19[^\n]", &id, name, &age, crime, status) == 5) {
                // Check if ID exists
                int exists = 0;
                CriminalNode *current = criminals.head;
                while (current != NULL) {
                    if (current->data.id == id) {
                        exists = 1;
                        break;
                    }
                    current = current->next;
                }
                
                if (!exists) {
                    CriminalNode *newNode = (CriminalNode*)malloc(sizeof(CriminalNode));
                    newNode->data.id = id;
                    strncpy(newNode->data.name, name, MAX_NAME_LEN - 1);
                    newNode->data.name[MAX_NAME_LEN - 1] = '\0';
                    newNode->data.age = age;
                    strncpy(newNode->data.crime, crime, MAX_CRIME_LEN - 1);
                    newNode->data.crime[MAX_CRIME_LEN - 1] = '\0';
                    strncpy(newNode->data.status, status, 19);
                    newNode->data.status[19] = '\0';
                    newNode->next = NULL;
                    
                    if (criminals.head == NULL) {
                        criminals.head = newNode;
                    } else {
                        current = criminals.head;
                        while (current->next != NULL) current = current->next;
                        current->next = newNode;
                    }
                    criminals.size++;
                    
                    addcrimact(id, "Added new criminal (batch)");
                    addcrimdet(&newNode->data, "Added new criminal (batch)");
                    success_count++;
                } else {
                    fail_count++;
                    char err_msg[100];
                    snprintf(err_msg, sizeof(err_msg), "ID %d already exists\n", id);
                    if (strlen(errors) < 1900) strcat(errors, err_msg);
                }
            } else {
                fail_count++;
                char err_msg[100];
                snprintf(err_msg, sizeof(err_msg), "Invalid format: %s\n", line);
                if (strlen(errors) < 1900) strcat(errors, err_msg);
            }
            
            line = strtok(NULL, "\n");
        }
        
        g_free(text);
        
        // Show results
        char result_msg[2500];
        snprintf(result_msg, sizeof(result_msg), 
                "Batch Add Results:\n\n"
                "✅ Successfully added: %d criminal(s)\n"
                "❌ Failed: %d\n\n%s",
                success_count, fail_count, 
                (fail_count > 0 && strlen(errors) > 0) ? errors : "");
        
        GtkWidget *result_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "%s", result_msg);
        gtk_dialog_run(GTK_DIALOG(result_dialog));
        gtk_widget_destroy(result_dialog);
        
        // Refresh the list if parent window exists
        if (parent) {
            GtkWidget *treeview = (GtkWidget*)g_object_get_data(G_OBJECT(parent), "treeview");
            if (treeview) refresh_criminal_list(treeview);
        }
    }
    gtk_widget_destroy(dialog);
}

void show_search_criminal_dialog(GtkWidget *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Search Criminal",
                                                     GTK_WINDOW(parent),
                                                     GTK_DIALOG_MODAL,
                                                     "Cancel", GTK_RESPONSE_CANCEL,
                                                     "Search", GTK_RESPONSE_ACCEPT,
                                                     NULL);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    GtkWidget *label = gtk_label_new("Criminal ID:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    GtkWidget *entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);

    gtk_container_add(GTK_CONTAINER(content), grid);
    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        int search_id = atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
        CriminalNode *current = criminals.head;
        while (current != NULL) {
            if (current->data.id == search_id) {
                char msg[500];
                snprintf(msg, sizeof(msg),
                        "Criminal Found:\n\nID: %d\nName: %s\nAge: %d\nCrime: %s\nStatus: %s",
                        current->data.id, current->data.name, current->data.age,
                        current->data.crime, current->data.status);
                
                GtkWidget *result_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                                   GTK_DIALOG_MODAL,
                                                                   GTK_MESSAGE_INFO,
                                                                   GTK_BUTTONS_OK,
                                                                   "%s", msg);
                gtk_dialog_run(GTK_DIALOG(result_dialog));
                gtk_widget_destroy(result_dialog);
                
                addcrimact(current->data.id, "Searched for criminal");
                gtk_widget_destroy(dialog);
                return;
            }
            current = current->next;
        }
        
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_ERROR,
                                                          GTK_BUTTONS_OK,
                                                          "Criminal not found!");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
    gtk_widget_destroy(dialog);
}

void show_update_criminal_dialog(GtkWidget *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Update Criminal",
                                                     GTK_WINDOW(parent),
                                                     GTK_DIALOG_MODAL,
                                                     "Cancel", GTK_RESPONSE_CANCEL,
                                                     "Update", GTK_RESPONSE_ACCEPT,
                                                     NULL);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    GtkWidget *id_label = gtk_label_new("Criminal ID:");
    gtk_grid_attach(GTK_GRID(grid), id_label, 0, 0, 1, 1);
    GtkWidget *id_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 1, 1);

    GtkWidget *entries[4];
    const char *labels[] = {"Name:", "Age:", "Crime:", "Status:"};

    for (int i = 0; i < 4; i++) {
        GtkWidget *label = gtk_label_new(labels[i]);
        gtk_widget_set_halign(label, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i + 1, 1, 1);
        entries[i] = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), entries[i], 1, i + 1, 1, 1);
    }

    gtk_container_add(GTK_CONTAINER(content), grid);
    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        int update_id = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));
        CriminalNode *current = criminals.head;
        
        while (current != NULL) {
            if (current->data.id == update_id) {
                const char *name = gtk_entry_get_text(GTK_ENTRY(entries[0]));
                int age = atoi(gtk_entry_get_text(GTK_ENTRY(entries[1])));
                const char *crime = gtk_entry_get_text(GTK_ENTRY(entries[2]));
                const char *status = gtk_entry_get_text(GTK_ENTRY(entries[3]));

                strncpy(current->data.name, name, MAX_NAME_LEN - 1);
                current->data.name[MAX_NAME_LEN - 1] = '\0';
                current->data.age = age;
                strncpy(current->data.crime, crime, MAX_CRIME_LEN - 1);
                current->data.crime[MAX_CRIME_LEN - 1] = '\0';
                strncpy(current->data.status, status, 19);
                current->data.status[19] = '\0';

                addcrimact(current->data.id, "Updated criminal details");
                addcrimdet(&current->data, "Updated criminal details");

                GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                                    GTK_DIALOG_MODAL,
                                                                    GTK_MESSAGE_INFO,
                                                                    GTK_BUTTONS_OK,
                                                                    "Criminal updated successfully!");
                gtk_dialog_run(GTK_DIALOG(success_dialog));
                gtk_widget_destroy(success_dialog);

                if (parent) {
                    GtkWidget *treeview = (GtkWidget*)g_object_get_data(G_OBJECT(parent), "treeview");
                    if (treeview) refresh_criminal_list(treeview);
                }
                gtk_widget_destroy(dialog);
                return;
            }
            current = current->next;
        }

        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_ERROR,
                                                          GTK_BUTTONS_OK,
                                                          "Criminal not found!");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
    gtk_widget_destroy(dialog);
}

void show_delete_criminal_dialog(GtkWidget *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Delete Criminal",
                                                     GTK_WINDOW(parent),
                                                     GTK_DIALOG_MODAL,
                                                     "Cancel", GTK_RESPONSE_CANCEL,
                                                     "Delete", GTK_RESPONSE_ACCEPT,
                                                     NULL);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    GtkWidget *label = gtk_label_new("Criminal ID:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    GtkWidget *entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);

    gtk_container_add(GTK_CONTAINER(content), grid);
    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        int delete_id = atoi(gtk_entry_get_text(GTK_ENTRY(entry)));

        if (criminals.head == NULL) {
            GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                              GTK_DIALOG_MODAL,
                                                              GTK_MESSAGE_ERROR,
                                                              GTK_BUTTONS_OK,
                                                              "No criminals to delete!");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
            gtk_widget_destroy(dialog);
            return;
        }

        if (criminals.head->data.id == delete_id) {
            CriminalNode *temp = criminals.head;
            criminals.head = criminals.head->next;
            free(temp);
            criminals.size--;
            addcrimact(delete_id, "Deleted criminal");

            GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                                GTK_DIALOG_MODAL,
                                                                GTK_MESSAGE_INFO,
                                                                GTK_BUTTONS_OK,
                                                                "Criminal deleted successfully!");
            gtk_dialog_run(GTK_DIALOG(success_dialog));
            gtk_widget_destroy(success_dialog);

            if (parent) {
                GtkWidget *treeview = (GtkWidget*)g_object_get_data(G_OBJECT(parent), "treeview");
                if (treeview) refresh_criminal_list(treeview);
            }
            gtk_widget_destroy(dialog);
            return;
        }

        CriminalNode *current = criminals.head;
        while (current->next != NULL) {
            if (current->next->data.id == delete_id) {
                CriminalNode *temp = current->next;
                current->next = current->next->next;
                free(temp);
                criminals.size--;
                addcrimact(delete_id, "Deleted criminal");

                GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                                    GTK_DIALOG_MODAL,
                                                                    GTK_MESSAGE_INFO,
                                                                    GTK_BUTTONS_OK,
                                                                    "Criminal deleted successfully!");
                gtk_dialog_run(GTK_DIALOG(success_dialog));
                gtk_widget_destroy(success_dialog);

                if (parent) {
                    GtkWidget *treeview = (GtkWidget*)g_object_get_data(G_OBJECT(parent), "treeview");
                    if (treeview) refresh_criminal_list(treeview);
                }
                gtk_widget_destroy(dialog);
                return;
            }
            current = current->next;
        }

        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_ERROR,
                                                          GTK_BUTTONS_OK,
                                                          "Criminal not found!");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
    gtk_widget_destroy(dialog);
}

static void on_refresh_criminal_clicked(GtkWidget *widget, gpointer data) {
    (void)data;
    GtkWidget *window = (GtkWidget*)g_object_get_data(G_OBJECT(widget), "window");
    if (window) {
        GtkWidget *treeview = (GtkWidget*)g_object_get_data(G_OBJECT(window), "treeview");
        if (treeview) refresh_criminal_list(treeview);
    }
}

static void on_criminal_manage_clicked(GtkWidget *widget, gpointer data) {
    (void)widget; (void)data;
    show_criminal_window();
}

// Case Management Window
void refresh_case_list(GtkWidget *treeview) {
    if (!treeview || !GTK_IS_TREE_VIEW(treeview)) return;
    
    GtkTreeView *tv = GTK_TREE_VIEW(treeview);
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(tv));
    gtk_list_store_clear(store);
    
    CaseNode *current = cases.front;
    while (current != NULL) {
        GtkTreeIter iter;
        char priority_str[10];
        snprintf(priority_str, sizeof(priority_str), "%s", current->data.priority == 1 ? "Urgent" : "Normal");
        
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                          0, current->data.caseid,
                          1, current->data.title,
                          2, current->data.description,
                          3, current->data.criminalid,
                          4, priority_str,
                          5, current->data.status,
                          -1);
        current = current->next;
    }
}

void show_case_window() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Case Management");
    gtk_window_set_default_size(GTK_WINDOW(window), 950, 650);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    apply_css_styling(window);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 15);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Title
    GtkWidget *title_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title_label), "<span size='large' weight='bold' foreground='#ecf0f1'>📋 Case Management (Queue - FIFO)</span>");
    gtk_widget_set_halign(title_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), title_label, FALSE, FALSE, 5);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 8);

    GtkWidget *add_btn = gtk_button_new_with_label("➕ Add Case");
    gtk_widget_set_size_request(add_btn, 130, 40);
    g_signal_connect(add_btn, "clicked", G_CALLBACK(show_add_case_dialog), window);
    gtk_box_pack_start(GTK_BOX(hbox), add_btn, FALSE, FALSE, 5);

    GtkWidget *add_multiple_btn = gtk_button_new_with_label("➕➕ Add Multiple");
    gtk_widget_set_size_request(add_multiple_btn, 140, 40);
    g_signal_connect(add_multiple_btn, "clicked", G_CALLBACK(show_add_multiple_cases_dialog), window);
    gtk_box_pack_start(GTK_BOX(hbox), add_multiple_btn, FALSE, FALSE, 5);

    GtkWidget *dequeue_btn = gtk_button_new_with_label("⬇️ Dequeue");
    gtk_widget_set_size_request(dequeue_btn, 130, 40);
    g_signal_connect(dequeue_btn, "clicked", G_CALLBACK(show_dequeue_case_dialog), window);
    gtk_box_pack_start(GTK_BOX(hbox), dequeue_btn, FALSE, FALSE, 5);

    GtkWidget *peek_btn = gtk_button_new_with_label("👁️ Peek");
    gtk_widget_set_size_request(peek_btn, 120, 40);
    g_signal_connect(peek_btn, "clicked", G_CALLBACK(show_peek_case_dialog), window);
    gtk_box_pack_start(GTK_BOX(hbox), peek_btn, FALSE, FALSE, 5);

    GtkWidget *urgent_btn = gtk_button_new_with_label("⚠️ Urgent Cases");
    gtk_widget_set_size_request(urgent_btn, 140, 40);
    gtk_widget_set_name(urgent_btn, "case-btn");
    g_signal_connect(urgent_btn, "clicked", G_CALLBACK(show_urgent_cases_dialog), window);
    gtk_box_pack_start(GTK_BOX(hbox), urgent_btn, FALSE, FALSE, 5);

    GtkWidget *refresh_btn = gtk_button_new_with_label("🔄 Refresh");
    gtk_widget_set_size_request(refresh_btn, 120, 40);
    g_object_set_data(G_OBJECT(refresh_btn), "window", window);
    g_signal_connect(refresh_btn, "clicked", G_CALLBACK(on_refresh_case_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), refresh_btn, FALSE, FALSE, 5);

    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 0);

    GtkListStore *store = gtk_list_store_new(6, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Case ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Title", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Description", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Criminal ID", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Priority", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Status", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    gtk_container_add(GTK_CONTAINER(scrolled), treeview);
    g_object_set_data(G_OBJECT(window), "treeview", treeview);

    refresh_case_list(treeview);
    gtk_widget_show_all(window);
}

void show_add_case_dialog(GtkWidget *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Add Case",
                                                     GTK_WINDOW(parent),
                                                     GTK_DIALOG_MODAL,
                                                     "Cancel", GTK_RESPONSE_CANCEL,
                                                     "Add", GTK_RESPONSE_ACCEPT,
                                                     NULL);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    GtkWidget *entries[6];
    const char *labels[] = {"Case ID:", "Title:", "Description:", "Criminal ID:", "Priority (1=Urgent, 0=Normal):", "Status:"};

    for (int i = 0; i < 6; i++) {
        GtkWidget *label = gtk_label_new(labels[i]);
        gtk_widget_set_halign(label, GTK_ALIGN_START);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i, 1, 1);
        entries[i] = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), entries[i], 1, i, 1, 1);
    }

    gtk_container_add(GTK_CONTAINER(content), grid);
    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        int caseid = atoi(gtk_entry_get_text(GTK_ENTRY(entries[0])));
        const char *title = gtk_entry_get_text(GTK_ENTRY(entries[1]));
        const char *description = gtk_entry_get_text(GTK_ENTRY(entries[2]));
        int criminalid = atoi(gtk_entry_get_text(GTK_ENTRY(entries[3])));
        int priority = atoi(gtk_entry_get_text(GTK_ENTRY(entries[4])));
        const char *status = gtk_entry_get_text(GTK_ENTRY(entries[5]));

        // Check if Case ID exists
        CaseNode *current = cases.front;
        while (current != NULL) {
            if (current->data.caseid == caseid) {
                GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                                  GTK_DIALOG_MODAL,
                                                                  GTK_MESSAGE_ERROR,
                                                                  GTK_BUTTONS_OK,
                                                                  "Case ID already exists!");
                gtk_dialog_run(GTK_DIALOG(error_dialog));
                gtk_widget_destroy(error_dialog);
                gtk_widget_destroy(dialog);
                return;
            }
            current = current->next;
        }

        CaseNode *newNode = (CaseNode*)malloc(sizeof(CaseNode));
        newNode->data.caseid = caseid;
        strncpy(newNode->data.title, title, MAX_CASE_TITLE_LEN - 1);
        newNode->data.title[MAX_CASE_TITLE_LEN - 1] = '\0';
        strncpy(newNode->data.description, description, 199);
        newNode->data.description[199] = '\0';
        newNode->data.criminalid = criminalid;
        newNode->data.priority = priority;
        strncpy(newNode->data.status, status, 19);
        newNode->data.status[19] = '\0';
        newNode->next = NULL;

        if (cases.front == NULL) {
            cases.front = cases.rear = newNode;
        } else {
            cases.rear->next = newNode;
            cases.rear = newNode;
        }
        cases.size++;

        addcaseact(caseid, "Added new case to queue");
        addcasedet(&newNode->data, "Added new case to queue");

        GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                            GTK_DIALOG_MODAL,
                                                            GTK_MESSAGE_INFO,
                                                            GTK_BUTTONS_OK,
                                                            "Case added successfully!");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);

        if (parent) {
            GtkWidget *treeview = (GtkWidget*)g_object_get_data(G_OBJECT(parent), "treeview");
            if (treeview) refresh_case_list(treeview);
        }
    }
    gtk_widget_destroy(dialog);
}

void show_add_multiple_cases_dialog(GtkWidget *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Add Multiple Cases",
                                                     GTK_WINDOW(parent),
                                                     GTK_DIALOG_MODAL,
                                                     "Cancel", GTK_RESPONSE_CANCEL,
                                                     "Add All", GTK_RESPONSE_ACCEPT,
                                                     NULL);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 700, 500);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    gtk_container_add(GTK_CONTAINER(content), vbox);

    // Instructions
    GtkWidget *info_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info_label), 
        "<span font='11'><b>Enter multiple cases (one per line):</b>\n"
        "Format: <tt>CaseID|Title|Description|CriminalID|Priority|Status</tt>\n"
        "Priority: 1=Urgent, 0=Normal\n"
        "Example: <tt>1001|Bank Robbery|Investigation of bank robbery|101|1|Open</tt></span>");
    gtk_label_set_line_wrap(GTK_LABEL(info_label), TRUE);
    gtk_widget_set_halign(info_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), info_label, FALSE, FALSE, 5);

    // Text view for batch input
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolled, 650, 350);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 5);

    GtkWidget *textview = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(scrolled), textview);

    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
        GtkTextIter start, end;
        gtk_text_buffer_get_bounds(buffer, &start, &end);
        gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        
        int success_count = 0;
        int fail_count = 0;
        char errors[2000] = "";
        
        // Parse each line
        char *line = strtok(text, "\n");
        while (line != NULL) {
            // Skip empty lines
            while (*line == ' ' || *line == '\t') line++;
            if (*line == '\0' || *line == '\n') {
                line = strtok(NULL, "\n");
                continue;
            }
            
            // Parse format: CaseID|Title|Description|CriminalID|Priority|Status
            int caseid, criminalid, priority;
            char title[100], description[200], status[20];
            if (sscanf(line, "%d|%99[^|]|%199[^|]|%d|%d|%19[^\n]", 
                       &caseid, title, description, &criminalid, &priority, status) == 6) {
                // Check if Case ID exists
                int exists = 0;
                CaseNode *current = cases.front;
                while (current != NULL) {
                    if (current->data.caseid == caseid) {
                        exists = 1;
                        break;
                    }
                    current = current->next;
                }
                
                if (!exists) {
                    CaseNode *newNode = (CaseNode*)malloc(sizeof(CaseNode));
                    newNode->data.caseid = caseid;
                    strncpy(newNode->data.title, title, MAX_CASE_TITLE_LEN - 1);
                    newNode->data.title[MAX_CASE_TITLE_LEN - 1] = '\0';
                    strncpy(newNode->data.description, description, 199);
                    newNode->data.description[199] = '\0';
                    newNode->data.criminalid = criminalid;
                    newNode->data.priority = priority;
                    strncpy(newNode->data.status, status, 19);
                    newNode->data.status[19] = '\0';
                    newNode->next = NULL;
                    
                    if (cases.front == NULL) {
                        cases.front = cases.rear = newNode;
                    } else {
                        cases.rear->next = newNode;
                        cases.rear = newNode;
                    }
                    cases.size++;
                    
                    addcaseact(caseid, "Added new case (batch)");
                    addcasedet(&newNode->data, "Added new case (batch)");
                    success_count++;
                } else {
                    fail_count++;
                    char err_msg[100];
                    snprintf(err_msg, sizeof(err_msg), "Case ID %d already exists\n", caseid);
                    if (strlen(errors) < 1900) strcat(errors, err_msg);
                }
            } else {
                fail_count++;
                char err_msg[100];
                snprintf(err_msg, sizeof(err_msg), "Invalid format: %s\n", line);
                if (strlen(errors) < 1900) strcat(errors, err_msg);
            }
            
            line = strtok(NULL, "\n");
        }
        
        g_free(text);
        
        // Show results
        char result_msg[2500];
        snprintf(result_msg, sizeof(result_msg), 
                "Batch Add Results:\n\n"
                "✅ Successfully added: %d case(s)\n"
                "❌ Failed: %d\n\n%s",
                success_count, fail_count, 
                (fail_count > 0 && strlen(errors) > 0) ? errors : "");
        
        GtkWidget *result_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "%s", result_msg);
        gtk_dialog_run(GTK_DIALOG(result_dialog));
        gtk_widget_destroy(result_dialog);
        
        // Refresh the list if parent window exists
        if (parent) {
            GtkWidget *treeview = (GtkWidget*)g_object_get_data(G_OBJECT(parent), "treeview");
            if (treeview) refresh_case_list(treeview);
        }
    }
    gtk_widget_destroy(dialog);
}

void show_dequeue_case_dialog(GtkWidget *parent) {
    if (cases.front == NULL) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                                    GTK_DIALOG_MODAL,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "Queue is empty!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    CaseNode *temp = cases.front;
    Case data = temp->data;
    cases.front = cases.front->next;
    if (cases.front == NULL) {
        cases.rear = NULL;
    }
    free(temp);
    cases.size--;

    addcaseact(data.caseid, "Dequeued case from queue");
    addcasedet(&data, "Dequeued case from queue");

    char msg[500];
    snprintf(msg, sizeof(msg),
            "Dequeued Case:\n\nCase ID: %d\nTitle: %s\nDescription: %s\nCriminal ID: %d\nPriority: %s\nStatus: %s",
            data.caseid, data.title, data.description, data.criminalid,
            data.priority == 1 ? "Urgent" : "Normal", data.status);

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "%s", msg);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    if (parent) {
        GtkWidget *treeview = (GtkWidget*)g_object_get_data(G_OBJECT(parent), "treeview");
        if (treeview) refresh_case_list(treeview);
    }
}

void show_peek_case_dialog(GtkWidget *parent) {
    if (cases.front == NULL) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                                    GTK_DIALOG_MODAL,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "Queue is empty!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    Case front = cases.front->data;
    addcaseact(front.caseid, "Peeked at front of queue");
    addcasedet(&front, "Peeked at front of queue");

    char msg[500];
    snprintf(msg, sizeof(msg),
            "Next Case to Process (Front):\n\nCase ID: %d\nTitle: %s\nDescription: %s\nCriminal ID: %d\nPriority: %s\nStatus: %s",
            front.caseid, front.title, front.description, front.criminalid,
            front.priority == 1 ? "Urgent" : "Normal", front.status);

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "%s", msg);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void show_urgent_cases_dialog(GtkWidget *parent) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Urgent Cases");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 400);
    if (parent && GTK_IS_WINDOW(parent)) {
        gtk_window_set_transient_for(GTK_WINDOW(window), GTK_WINDOW(parent));
    }

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 0);

    GtkListStore *store = gtk_list_store_new(6, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Case ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Title", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Description", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Criminal ID", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Priority", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Status", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    CaseNode *current = cases.front;
    int urgent_count = 0;
    while (current != NULL) {
        if (current->data.priority == 1) {
            GtkTreeIter iter;
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                              0, current->data.caseid,
                              1, current->data.title,
                              2, current->data.description,
                              3, current->data.criminalid,
                              4, "Urgent",
                              5, current->data.status,
                              -1);
            urgent_count++;
        }
        current = current->next;
    }

    if (urgent_count == 0) {
        GtkWidget *label = gtk_label_new("No urgent cases found.");
        gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 10);
    } else {
        gtk_container_add(GTK_CONTAINER(scrolled), treeview);
        GtkWidget *label = gtk_label_new(g_strdup_printf("Total urgent cases: %d", urgent_count));
        gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);
    }

    gtk_widget_show_all(window);
}

static void on_refresh_case_clicked(GtkWidget *widget, gpointer data) {
    (void)data;
    GtkWidget *window = (GtkWidget*)g_object_get_data(G_OBJECT(widget), "window");
    if (window) {
        GtkWidget *treeview = (GtkWidget*)g_object_get_data(G_OBJECT(window), "treeview");
        if (treeview) refresh_case_list(treeview);
    }
}

static void on_case_manage_clicked(GtkWidget *widget, gpointer data) {
    (void)widget; (void)data;
    show_case_window();
}

// Network Management Window
void refresh_network_list(GtkWidget *treeview) {
    if (!treeview || !GTK_IS_TREE_VIEW(treeview)) return;
    
    GtkTreeView *tv = GTK_TREE_VIEW(treeview);
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(tv));
    gtk_list_store_clear(store);
    
    for (int i = 0; i < criminal_network.num_connections; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                          0, criminal_network.connections[i].criminal1id,
                          1, criminal_network.connections[i].criminal2id,
                          -1);
    }
}

void show_network_window() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Criminal Network");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 500);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    apply_css_styling(window);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 15);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Title
    GtkWidget *title_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title_label), "<span size='large' weight='bold' foreground='#ecf0f1'>🌐 Criminal Network</span>");
    gtk_widget_set_halign(title_label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), title_label, FALSE, FALSE, 5);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 8);

    GtkWidget *add_btn = gtk_button_new_with_label("➕ Add Connection");
    gtk_widget_set_size_request(add_btn, 180, 40);
    gtk_widget_set_name(add_btn, "network-btn");
    g_signal_connect(add_btn, "clicked", G_CALLBACK(show_add_connection_dialog), window);
    gtk_box_pack_start(GTK_BOX(hbox), add_btn, FALSE, FALSE, 5);

    GtkWidget *refresh_btn = gtk_button_new_with_label("🔄 Refresh");
    gtk_widget_set_size_request(refresh_btn, 120, 40);
    g_object_set_data(G_OBJECT(refresh_btn), "window", window);
    g_signal_connect(refresh_btn, "clicked", G_CALLBACK(on_refresh_network_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), refresh_btn, FALSE, FALSE, 5);

    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 0);

    GtkListStore *store = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_INT);
    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Criminal 1", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Criminal 2", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    gtk_container_add(GTK_CONTAINER(scrolled), treeview);
    g_object_set_data(G_OBJECT(window), "treeview", treeview);

    refresh_network_list(treeview);
    gtk_widget_show_all(window);
}

void show_add_connection_dialog(GtkWidget *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Add Connection",
                                                     GTK_WINDOW(parent),
                                                     GTK_DIALOG_MODAL,
                                                     "Cancel", GTK_RESPONSE_CANCEL,
                                                     "Add", GTK_RESPONSE_ACCEPT,
                                                     NULL);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    GtkWidget *label1 = gtk_label_new("Criminal ID 1:");
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 1, 1);
    GtkWidget *entry1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry1, 1, 0, 1, 1);

    GtkWidget *label2 = gtk_label_new("Criminal ID 2:");
    gtk_grid_attach(GTK_GRID(grid), label2, 0, 1, 1, 1);
    GtkWidget *entry2 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry2, 1, 1, 1, 1);

    gtk_container_add(GTK_CONTAINER(content), grid);
    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        int id1 = atoi(gtk_entry_get_text(GTK_ENTRY(entry1)));
        int id2 = atoi(gtk_entry_get_text(GTK_ENTRY(entry2)));

        if (criminal_network.num_connections >= MAX_CONNECTIONS) {
            GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                              GTK_DIALOG_MODAL,
                                                              GTK_MESSAGE_ERROR,
                                                              GTK_BUTTONS_OK,
                                                              "Maximum connections reached!");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
            gtk_widget_destroy(dialog);
            return;
        }

        criminal_network.connections[criminal_network.num_connections].criminal1id = id1;
        criminal_network.connections[criminal_network.num_connections].criminal2id = id2;
        criminal_network.num_connections++;

        GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                            GTK_DIALOG_MODAL,
                                                            GTK_MESSAGE_INFO,
                                                            GTK_BUTTONS_OK,
                                                            "Connection added successfully!");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);

        if (parent) {
            GtkWidget *treeview = (GtkWidget*)g_object_get_data(G_OBJECT(parent), "treeview");
            if (treeview) refresh_network_list(treeview);
        }
    }
    gtk_widget_destroy(dialog);
}

static void on_refresh_network_clicked(GtkWidget *widget, gpointer data) {
    (void)data;
    GtkWidget *window = (GtkWidget*)g_object_get_data(G_OBJECT(widget), "window");
    if (window) {
        GtkWidget *treeview = (GtkWidget*)g_object_get_data(G_OBJECT(window), "treeview");
        if (treeview) refresh_network_list(treeview);
    }
}

static void on_network_manage_clicked(GtkWidget *widget, gpointer data) {
    (void)widget; (void)data;
    show_network_window();
}

// History Viewing
void show_criminal_history_dialog(GtkWidget *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("View Criminal History",
                                                     GTK_WINDOW(parent),
                                                     GTK_DIALOG_MODAL,
                                                     "Cancel", GTK_RESPONSE_CANCEL,
                                                     "View", GTK_RESPONSE_ACCEPT,
                                                     NULL);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    GtkWidget *label = gtk_label_new("Criminal ID:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    GtkWidget *entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);

    gtk_container_add(GTK_CONTAINER(content), grid);
    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        int id = atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
        gtk_widget_destroy(dialog);
        
        // Create a window to show history
        GtkWidget *hist_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(hist_window), "Criminal Detailed History");
        gtk_window_set_default_size(GTK_WINDOW(hist_window), 700, 500);
        if (parent && GTK_IS_WINDOW(parent)) {
            gtk_window_set_transient_for(GTK_WINDOW(hist_window), GTK_WINDOW(parent));
        }

        GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_container_add(GTK_CONTAINER(hist_window), scrolled);

        GtkWidget *textview = gtk_text_view_new();
        gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), FALSE);
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
        gtk_container_add(GTK_CONTAINER(scrolled), textview);

        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
        GtkTextIter iter;
        gtk_text_buffer_get_start_iter(buffer, &iter);

        // Get history data and format it using findall function
        char hist_text[10000] = "";
        char temp[300];
        
        // Show simple action history first
        HistArr *histarr = gethist1();
        snprintf(temp, sizeof(temp), "=== CRIMINAL ACTION HISTORY (ID: %d) ===\n\n", id);
        strcat(hist_text, temp);
        
        int found_simple = 0;
        int action_num = 0;
        if (histarr->count > 0) {
            for (int i = 0; i < histarr->count; i++) {
                if (histarr->entries[i].id == id) {
                    found_simple = 1;
                    action_num++;
                    snprintf(temp, sizeof(temp), "%d. %s\n", action_num, histarr->entries[i].action);
                    strcat(hist_text, temp);
                }
            }
        }
        
        if (!found_simple) {
            strcat(hist_text, "No action history recorded.\n");
        }
        
        // Show detailed history
        char temp2[300];
        snprintf(temp2, sizeof(temp2), "\n=== DETAILED CRIMINAL HISTORY (ID: %d) ===\n\n", id);
        strcat(hist_text, temp2);
        
        CrimArr *crimarr = getcrimarr();
        int found_detailed = 0;
        
        // Use direct iteration (findall is not exported, direct access is simpler)
        int entry_counter = 0;
        for (int i = 0; i < crimarr->count; i++) {
            if (crimarr->entries[i].criminalid == id) {
                found_detailed = 1;
                entry_counter++;
                CrimDetail *e = &crimarr->entries[i];
                char entry[600];
                snprintf(entry, sizeof(entry),
                        "Entry %d:\nAction: %s\nName: %s\nAge: %d\nCrime: %s\nStatus: %s\n\n",
                        entry_counter, e->action, e->name, e->age, e->crime, e->status);
                strcat(hist_text, entry);
            }
        }

        if (!found_detailed) {
            strcat(hist_text, "No detailed history for this criminal ID.\n");
        }
        
        if (!found_simple && !found_detailed) {
            char info_msg[200];
            snprintf(info_msg, sizeof(info_msg), 
                    "\nNote: History is only recorded when actions are performed (add, update, delete, search).\n"
                    "Try performing an action on criminal ID %d first, then view history again.", id);
            strcat(hist_text, info_msg);
        }

        gtk_text_buffer_set_text(buffer, hist_text, -1);
        gtk_widget_show_all(hist_window);
        return;
    }
    gtk_widget_destroy(dialog);
}

void show_case_history_dialog(GtkWidget *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("View Case History",
                                                     GTK_WINDOW(parent),
                                                     GTK_DIALOG_MODAL,
                                                     "Cancel", GTK_RESPONSE_CANCEL,
                                                     "View", GTK_RESPONSE_ACCEPT,
                                                     NULL);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    GtkWidget *label = gtk_label_new("Criminal ID:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    GtkWidget *entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);

    gtk_container_add(GTK_CONTAINER(content), grid);
    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        int criminal_id = atoi(gtk_entry_get_text(GTK_ENTRY(entry)));
        gtk_widget_destroy(dialog);
        
        GtkWidget *hist_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(hist_window), "Case Detailed History");
        gtk_window_set_default_size(GTK_WINDOW(hist_window), 700, 500);
        if (parent && GTK_IS_WINDOW(parent)) {
            gtk_window_set_transient_for(GTK_WINDOW(hist_window), GTK_WINDOW(parent));
        }

        GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_container_add(GTK_CONTAINER(hist_window), scrolled);

        GtkWidget *textview = gtk_text_view_new();
        gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), FALSE);
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
        gtk_container_add(GTK_CONTAINER(scrolled), textview);

        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
        char hist_text[10000] = "";
        
        // Show simple action history first
        HistArr *histarr = gethist2();
        char temp_simple[300];
        snprintf(temp_simple, sizeof(temp_simple), "=== CASE ACTION HISTORY (Criminal ID: %d) ===\n\n", criminal_id);
        strcat(hist_text, temp_simple);
        
        int found_simple = 0;
        int action_num = 0;
        if (histarr->count > 0) {
            // Find cases for this criminal first
            CaseArr *casearr = getcasearr();
            for (int i = 0; i < histarr->count; i++) {
                // Check if this action is for a case belonging to this criminal
                for (int j = 0; j < casearr->count; j++) {
                    if (casearr->entries[j].criminalid == criminal_id && 
                        histarr->entries[i].id == casearr->entries[j].caseid) {
                        found_simple = 1;
                        action_num++;
                        char action_entry[200];
                        snprintf(action_entry, sizeof(action_entry), "%d. %s\n", action_num, histarr->entries[i].action);
                        strcat(hist_text, action_entry);
                        break;
                    }
                }
            }
        }
        
        if (!found_simple) {
            strcat(hist_text, "No action history recorded.\n");
        }
        
        // Show detailed history
        char temp_detailed[300];
        snprintf(temp_detailed, sizeof(temp_detailed), "\n=== DETAILED CASE HISTORY (Criminal ID: %d) ===\n\n", criminal_id);
        strcat(hist_text, temp_detailed);
        
        CaseArr *casearr2 = getcasearr();
        int found_detailed = 0;
        int entry_counter = 0;
        
        // Use direct iteration to find all cases for this criminal
        for (int i = 0; i < casearr2->count; i++) {
            if (casearr2->entries[i].criminalid == criminal_id) {
                found_detailed = 1;
                entry_counter++;
                CaseDetail *e = &casearr2->entries[i];
                char entry[600];
                char priority_str[10];
                snprintf(priority_str, sizeof(priority_str), "%s", e->priority == 1 ? "Urgent" : "Normal");
                snprintf(entry, sizeof(entry),
                        "Entry %d:\nAction: %s\nCase ID: %d\nTitle: %s\nDescription: %s\nPriority: %s\nStatus: %s\n\n",
                        entry_counter, e->action, e->caseid, e->title, e->description, priority_str, e->status);
                strcat(hist_text, entry);
            }
        }

        if (!found_detailed) {
            strcat(hist_text, "No detailed history found for this criminal ID.\n");
        }
        
        if (!found_simple && !found_detailed) {
            char info_msg[200];
            snprintf(info_msg, sizeof(info_msg), 
                    "\nNote: History is only recorded when actions are performed (add, update, delete, peek, dequeue).\n"
                    "Try performing an action on cases for criminal ID %d first, then view history again.", criminal_id);
            strcat(hist_text, info_msg);
        }

        gtk_text_buffer_set_text(buffer, hist_text, -1);
        gtk_widget_show_all(hist_window);
        return;
    }
    gtk_widget_destroy(dialog);
}

void show_change_log_window() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Change Log");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(window), scrolled);

    GtkWidget *textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(scrolled), textview);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    char log_text[10000] = "";
    strcat(log_text, "=== CHANGE LOG ===\n\n");

    extern LogEntry logentries[];
    extern int logcnt;

    for (int i = 0; i < logcnt; i++) {
        char entry[250];
        snprintf(entry, sizeof(entry), "[%s] %s\n", 
                 logentries[i].timestamp, logentries[i].message);
        strcat(log_text, entry);
    }

    if (logcnt == 0) {
        strcat(log_text, "No log entries found.\n");
    }

    gtk_text_buffer_set_text(buffer, log_text, -1);
    gtk_widget_show_all(window);
}

static void on_criminal_history_clicked(GtkWidget *widget, gpointer data) {
    (void)widget; (void)data;
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *parent = (GTK_IS_WINDOW(toplevel)) ? toplevel : NULL;
    show_criminal_history_dialog(parent);
}

static void on_case_history_clicked(GtkWidget *widget, gpointer data) {
    (void)widget; (void)data;
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    GtkWidget *parent = (GTK_IS_WINDOW(toplevel)) ? toplevel : NULL;
    show_case_history_dialog(parent);
}

static void on_change_log_clicked(GtkWidget *widget, gpointer data) {
    (void)widget; (void)data;
    show_change_log_window();
}

// Entry point
void start_gui(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    initCriminalList(&criminals);
    initCaseQueue(&cases);
    initGraph(&criminal_network);
    inithist();

    loadcrim(&criminals);
    loadcase(&cases);

    show_main_window();

    gtk_main();

    savecrim(&criminals);
    savecase(&cases);
}

