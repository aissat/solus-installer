/* Copyright 2015 Michael Rutherford
*
* This file is part of solus-installer.
*
* solus-installer is free software: you can redistribute it
* and/or modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation, either version 2 of the
* License, or (at your option) any later version.
*
* solus-installer is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with solus-installer. If not, see http://www.gnu.org/licenses/.
*/

//Imported header files
#include <gtk/gtk.h>
#include <stdlib.h>

//Function prototypes
static void quit_installer (GtkWidget* window, gpointer user_data);
static void install_warning (GtkWidget* window, gpointer user_data);
static void change_log (GtkWidget* window, gpointer user_data);

//Function to destroy the window so that the installer quits
static void quit_installer (GtkWidget* window, gpointer user_data) {
        gtk_widget_destroy (window);
        exit (0);
}

//Function to display an installation warning
/*
static void install_warning (GtkWidget* window, gpointer user_data) {
        //Declaration of the warning dialog and text
        GtkWidget* warning_dialog;
        GtkWidget* warning_text;

        //Instantiation of the warning dialog
        warning_dialog = gtk_message_dialog_new (GTK_WINDOW (window), 
                                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                                 GTK_MESSAGE_WARNING,
                                                 GTK_BUTTONS_OK,
                                                 "Installing Solus will erase the contents of the disk.");
        gtk_window_set_title (GTK_WINDOW (warning_dialog), "Warning");
        g_signal_connect_swapped (warning_dialog, "response", G_CALLBACK (gtk_widget_destroy), warning_dialog);

        //Shows the warning dialog widget
        gtk_dialog_show_all (warning_dialog);
}
*/

//Function to display changelog for Solus
static void change_log (GtkWidget* window, gpointer user_data) {
        //Declaration of the changelog dialog
        GtkWidget* new_dialog;

        //Instantiation of the changelog dialog
        new_dialog = gtk_message_dialog_new (GTK_WINDOW (window), 
                                             GTK_DIALOG_DESTROY_WITH_PARENT,
                                             GTK_MESSAGE_WARNING,
                                             GTK_BUTTONS_OK,
                                             "Solus Release #");
        gtk_window_set_title (GTK_WINDOW (new_dialog), "What's New?");
        g_signal_connect_swapped (new_dialog, "response", G_CALLBACK (gtk_widget_destroy), new_dialog);

        //Shows the changelog dialog widget
        gtk_dialog_run (GTK_DIALOG (new_dialog));
}

//Function that is activated by the main function
static void activate (GtkApplication* app, gpointer user_data) {
        //Declaration/instantiation of the window and notebook 
        GtkWidget* window = gtk_application_window_new (app);
        GtkWidget* notebook = gtk_notebook_new ();
        
        //Declaration/instantiation of the button boxes
        GtkWidget* welcome_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        GtkWidget* date_time_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        GtkWidget* users_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        GtkWidget* partition_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        
        //Declaration/instantiation of the tab labels
        GtkWidget* welcome_label = gtk_label_new ("Welcome");
        GtkWidget* date_time_label = gtk_label_new ("Date/Time");
        GtkWidget* users_label = gtk_label_new ("Users");
        GtkWidget* partition_label = gtk_label_new ("Partioning");
        
        //Declaration/instantiation of the new button and the icon
        GtkWidget* new_button = gtk_button_new_with_label ("What's New In Solus?");
        GtkWidget* new_icon = gtk_image_new_from_file ("new.png");
        
        //Declaration/instantiation of the livecd button and the icon
        GtkWidget* livecd_button = gtk_button_new_with_label ("Keep Using LiveCD");
        GtkWidget* livecd_icon = gtk_image_new_from_file ("live.png");
        
        //Declaration/instantiation of the install button and the icon
        GtkWidget* install_icon = gtk_image_new_from_file ("install.png");
        GtkWidget* install_button = gtk_button_new_with_label ("Install Solus");

        //Declaration/instantiation of the menu buttons
        GtkWidget* region_menu_button = gtk_menu_button_new ();
        GtkWidget* city_menu_button = gtk_menu_button_new ();

        //Declaration/instantiation of the menus
        GMenu* region_menu = g_menu_new ();
        GMenu* city_menu = g_menu_new ();

        //Declaration/instantiation of the region menu items
        GtkWidget* region_menu_item_america = gtk_menu_item_new_with_label ("America");
        GtkWidget* region_menu_item_not_america = gtk_menu_item_new_with_label ("Everywhere else");

        //Declaration/instantiation of the city menu items
        GtkWidget* city_menu_item_chicago = gtk_menu_item_new_with_label ("Chicago");

        //Assigns properties to the window
        gtk_window_set_title (GTK_WINDOW (window), "solus-installer");
        gtk_window_set_icon_from_file (GTK_WINDOW (window), "live.png", NULL);
        gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
        gtk_window_set_default_size (GTK_WINDOW (window), 750, 350);
        gtk_window_set_resizable (GTK_WINDOW (window), TRUE);
        
        //Sets the tabs positions and adds pages with labels
        gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), welcome_button_box, welcome_label, 0);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), date_time_button_box, date_time_label, 1);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), users_button_box, users_label, 2);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), partition_button_box, partition_label, 3);

        //Sets button box layouts
        gtk_button_box_set_layout (GTK_BUTTON_BOX (welcome_button_box), GTK_BUTTONBOX_SPREAD);
        gtk_button_box_set_layout (GTK_BUTTON_BOX (date_time_button_box), GTK_BUTTONBOX_SPREAD);

        //Assigns an image to the livecd button and connects an activity to the button 
        gtk_button_set_always_show_image (GTK_BUTTON (livecd_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (livecd_button), livecd_icon);
        gtk_button_set_image_position (GTK_BUTTON (livecd_button), GTK_POS_TOP);
        g_signal_connect_swapped (livecd_button, "clicked", G_CALLBACK (quit_installer), window);
        
        //Assigns an image to the changelog button and connects an activity to the button 
        gtk_button_set_always_show_image (GTK_BUTTON (new_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (new_button), new_icon);
        gtk_button_set_image_position (GTK_BUTTON (new_button), GTK_POS_TOP);
        g_signal_connect_swapped (new_button, "clicked", G_CALLBACK (change_log), window);

        //Assigns an image to the install button and connects an activity to the button 
        gtk_button_set_always_show_image (GTK_BUTTON (install_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (install_button), install_icon);
        gtk_button_set_image_position (GTK_BUTTON (install_button), GTK_POS_TOP);
        g_signal_connect_swapped (install_button, "clicked", G_CALLBACK (gtk_notebook_next_page), notebook);

        //Adds the region menu to the region menu button and adds regions to the menu
        gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (region_menu_button), G_MENU_MODEL (region_menu));
        g_menu_append (region_menu, "America", "america.region");

        //Adds the city menu to the city menu button and adds cities to the menu
        gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (city_menu_button), G_MENU_MODEL (city_menu));
        g_menu_append (city_menu, "Chicago", "chicago.city");

        //Adds buttons to button boxes
        gtk_container_add (GTK_CONTAINER (window), notebook);
        gtk_container_add (GTK_CONTAINER (welcome_button_box), livecd_button);
        gtk_container_add (GTK_CONTAINER (welcome_button_box), new_button);
        gtk_container_add (GTK_CONTAINER (welcome_button_box), install_button);
        gtk_container_add (GTK_CONTAINER (date_time_button_box), region_menu_button);
        gtk_container_add (GTK_CONTAINER (date_time_button_box), city_menu_button);

        //Displays the window and all the widgets attached to it
        gtk_widget_show_all (window);
}

//Main function
int main (int argc, char **argv) {
        //Declaration of the GtkApplicaton and status
        GtkApplication* app;
        int status;
        
        //Instantiation of the GtkApplication and the status
        app = gtk_application_new ("com.solus-project.installer", G_APPLICATION_FLAGS_NONE);
        g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
        status = g_application_run (G_APPLICATION (app), argc, argv);
        g_object_unref (app);
        
        //Returns the status of the applicaton 
        return status;
}
