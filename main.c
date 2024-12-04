#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>
#include "functions.h"

GtkWidget *button_box1,*button_box2;

void draw_card_clicked_cb(GtkButton *button, gpointer userdata){
    GtkWidget *button_box1 = GTK_WIDGET(userdata);
    //get image file path
    const char *imagepath = generate_random_card();
    //create image
    GtkWidget *image = gtk_image_new_from_file(imagepath);
    //make new button with image
    GtkWidget *new_button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(new_button),image);
    //store image path in button data
    g_object_set_data(G_OBJECT(new_button),"image-path",(gpointer)imagepath);
    //put new_button in button_box1
    gtk_box_pack_start(GTK_BOX(button_box1),new_button,TRUE,TRUE,0);
    gtk_widget_show_all(button_box1);
    //connect new button
    g_signal_connect(new_button,"clicked",G_CALLBACK(on_new_button_clicked),gtk_image);
}

void on_new_button_clicked(GtkWidget *new_button, GtkWidget *gtk_image){
    //get new_button imagepath
    const gchar *imagepath = (const gchar *) g_object_get_data(G_OBJECT(new_button),"image-path");
    //update center_image
    gtk_image_set_from_file(GTK_IMAGE(center_image),imagepath);
    //remove
    GtkWidget *parent_box = gtk_widget_get_parent(new_button);
    gtk_container_remove(GTK_CONTAINER(parent_box),new_button);
    gtk_widget_destroy(new_button);

}

int main(int argc, char *argv[]){
    GtkBuilder *builder;
    GtkWidget *window,*center_image, *draw_card;
  
    gtk_init(&argc, &argv);
    //get glade file
    builder = gtk_builder_new_from_file("glade.glade");
    //get main window
    window = GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
    //get box1
    button_box1 = GTK_WIDGET(gtk_builder_get_object(builder,"button_box1"));
    //get box2
    button_box2 = GTK_WIDGET(gtk_builder_get_object(builder,"button_box1"));
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





    //GtkWidget *image = gtk_image_new_from_file("cards/red7.png");
    //
    