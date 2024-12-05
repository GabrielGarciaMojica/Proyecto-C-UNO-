#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>
#include "functions.h"

GtkWidget *button_box1,*button_box2,*center_image;

void on_new_button_clicked(GtkWidget *new_button, gpointer userdata) {
    //Retrieve the image path stored in the button
    const gchar *imagepath = (const gchar *)g_object_get_data(G_OBJECT(new_button), "image-path");
    //Update the center image with the button's image
    if (imagepath) {
        
        gtk_image_set_from_file(GTK_IMAGE(center_image), imagepath);
    } else {
        g_warning("Image path not set for button.");
    }
    // Remove the button from its parent container
    GtkWidget *parent_box = gtk_widget_get_parent(new_button);
    gtk_container_remove(GTK_CONTAINER(parent_box), new_button);
    gtk_widget_destroy(new_button);
}


void draw_card_clicked_cb(GtkButton *button, gpointer userdata) {
    GtkWidget *button_box1 = GTK_WIDGET(userdata);

    // Generate a new random card image path
    const char *imagepath = generate_random_card();
    if (!imagepath) {
        g_warning("Failed to generate a random card.");
        return;
    }
    //Duplicate the image path to ensure each button has its own copy
    char *imagepath_copy = g_strdup(imagepath);
    //Create an image widget for the button
    GtkWidget *image = gtk_image_new_from_file(imagepath);
    if (!gtk_image_get_pixbuf(GTK_IMAGE(image))) {
        g_warning("Failed to load image from file: %s", imagepath);
        g_free(imagepath_copy);
        return;
    }
    //Create a new button and set the image
    GtkWidget *new_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(new_button), image);
    //Store the duplicated image path in the button's data
    g_object_set_data_full(G_OBJECT(new_button), "image-path", imagepath_copy, g_free);
    //Add the button to the button box
    gtk_box_pack_start(GTK_BOX(button_box1), new_button, TRUE, TRUE, 0);
    //Show all widgets in the box
    gtk_widget_show_all(button_box1);
    //Connect the button's "clicked" signal to the handler
    g_signal_connect(new_button, "clicked", G_CALLBACK(on_new_button_clicked), NULL);
}



int main(int argc, char *argv[]){
    GtkBuilder *builder;
    GtkWidget *window, *draw_card;
  
    gtk_init(&argc, &argv);
    //get glade file
    builder = gtk_builder_new_from_file("glade.glade");
    //get main window
    window = GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
    //get box1
    button_box1 = GTK_WIDGET(gtk_builder_get_object(builder,"button_box1"));
    //get box2
    button_box2 = GTK_WIDGET(gtk_builder_get_object(builder,"button_box2"));
    //get centerdeck
    center_image = GTK_WIDGET(gtk_builder_get_object(builder,"centerdeck")); 
    //get button1
    draw_card = GTK_WIDGET(gtk_builder_get_object(builder,"draw_card"));
    //connect drawcard signal
    g_signal_connect(draw_card,"clicked",G_CALLBACK(draw_card_clicked_cb),button_box1); 

    //show window
    gtk_widget_show_all(window);
    //enable terminal when close window 
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit),NULL);    
    //gtkmain loop
    gtk_main();

    return 0;
}