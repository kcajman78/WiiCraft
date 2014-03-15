#include <iostream>
#include <fstream>
#include <gccore.h>
#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <wiikeyboard/keyboard.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fat.h>
#include <sdcard/wiisd_io.h>
#include <png.h>
#include <pngu.h>
#include <network.h>
#include <sys/stat.h>

#include "common.h"
#include "update.h"
#include "main.h"
#include "utils.h"
#include "update.h"
#include "debug.h"

using namespace std;

bool netoworkRAN = false;
s8 selected = 1;

//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
void Update(){
	clear();
	if(netoworkRAN == false){
		printf("Initializing Network...");
		Debug("Initializing Network...");
		initialise_network();
		Debug("initialise_network() Done");
		netoworkRAN = true;
		fatInitDefault();
		Debug("fatInitDefault() Done");
	}
	clear();
	while(true) {
		printf("\x1b[2;0H");
		CHANGE_COLOR(MAGENTA);
		printf("WiiCraft is Stored on?\n");
		CHANGE_COLOR(WHITE);
		MENU("SD Card", 1); // MENU(description, option number)
		MENU("USB/HDD(Not Working)", 2);
		do {pressed = DetectInput(DI_BUTTONS_DOWN);} while(!pressed);
		if (pressed & WPAD_BUTTON_DOWN) {
			selected++;
			if (selected>2) selected = 1;
			continue;
		}
		if (pressed & WPAD_BUTTON_UP) {
			selected--;
			if (selected<1) selected = 2;
			continue;
		}
		if (pressed & WPAD_BUTTON_A) {
			if(selected == 1) {
				fatDevice = FAT_DEVICE_SD;
				#ifdef USBGECKO
				Debug("UPDATE:		fatDevice = FAT_DEVICE_SD.");
				#endif
				goto NEXT;
			}
			if(selected == 2) {
				fatDevice = FAT_DEVICE_USB;
				#ifdef USBGECKO
				Debug("UPDATE:		fatDevice = FAT_DEVICE_USB.");
				#endif
				goto NEXT;
			}
		}
	}
	NEXT:downloadUpdate();
	clear();
	return;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
void downloadUpdate(){
	printf("Attempting to connect to server...\n");
	s32 main_server = server_connect();
	printf("Connection established.\n\n");
	
	if(fatDevice == FAT_DEVICE_SD){
		mkdir("sd:/wiicraft",  S_IRWXU|S_IRGRP|S_IXGRP);
		remove( "sd:/wiicraft/wiicraft.dol");
	}
	else if(fatDevice == FAT_DEVICE_USB){
		mkdir("USB:/wiicraft",  S_IRWXU|S_IRGRP|S_IXGRP);
		remove( "USB:/wiicraft/wiicraft.dol");
	}
	
	// Open file
	FILE *f;
	if(fatDevice == FAT_DEVICE_SD){
		f=fopen("sd:/wiicraft/wiicraft.dol", "wb");
	}
	else{
		f=fopen("USB:/wiicraft/wiicraft.dol", "wb");
	}
	
	// If file can't be created
	if (f == NULL) {
		fclose(f);
		die("There was a problem creating/accessing the temp file.\n");
	}
	
	printf("Installing WiiCraft...");
	
	char http_request[1000];
	strcpy(http_request,"GET /wiicraft/wiicraft.dol");
	strcat(http_request, " HTTP/1.0\r\nHost: minepocket.azurewebsites.net\r\n\r\n");
	
	write_http_reply(main_server, http_request); // Send the HTTP message
	int result = request_file(main_server, f); // Store the servers reply in our file pointer

	fclose(f);
	net_close(main_server);
	
	if (result == true) {
		printf("\n\nSuccessfully downloaded WiiCraft.dol.\n");
	}
	else {
		die("\n\nDownload of WiiCraft.dol failed.\n");
	}
	printf("Updating meta.xml and icon.png...\n");
	usleep(3000000);
	downloadXML_AND_PNGUpdate();
	printf("Installing New Launcher...\n");
	usleep(3000000);
	downloadLauncher();
	printf("\nInstalled WiiCraft Successfully...\n");
	usleep(3000000);
	printf("\nExiting...\n");
	usleep(5000000);
	clear();
	return;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
void downloadXML_AND_PNGUpdate(){
	printf("Downloading meta.xml...\n");
	printf("Attempting to connect to server...\n");
	s32 main_server = server_connect();
	printf("Connection established.\n\n");
	
	if(fatDevice == FAT_DEVICE_SD){
		remove( "sd:/apps/wiicraft/meta.xml" );
	}
	else if(fatDevice == FAT_DEVICE_USB){
		remove( "USB:/apps/wiicraft/meta.xml" );
	}
	
	// Open file
	FILE *f;
	if(fatDevice == FAT_DEVICE_SD){
		f=fopen("sd:/apps/wiicraft/meta.xml", "wb");
	}
	else{
		f=fopen("USB:/apps/wiicraft/meta.xml", "wb");
	}
	
	// If file can't be created
	if (f == NULL) {
		fclose(f);
		die("There was a problem creating/accessing the temp file.\n");
	}
	
	printf("Downloading Update");
	
	char http_request[1000];
	strcpy(http_request,"GET /wiicraft/meta.xml");
	strcat(http_request, " HTTP/1.0\r\nHost: minepocket.azurewebsites.ne\r\n\r\n");
	
	write_http_reply(main_server, http_request); // Send the HTTP message
	int result = request_file(main_server, f); // Store the servers reply in our file pointer

	fclose(f);
	net_close(main_server);
	
	if (result == true) {
		printf("\n\nSuccessfully downloaded the XML File.\n");
	}
	else {
		die("\n\nDownload of XML file failed.\n");
	}
	usleep(5000000);
	printf("\n\nDownloading icon.png...\n");
	printf("Attempting to connect to server...\n");
	main_server = server_connect();
	printf("Connection established.\n\n");
	
	if(fatDevice == FAT_DEVICE_SD){
		remove( "sd:/apps/wiicraft/icon.png" );
	}
	else if(fatDevice == FAT_DEVICE_USB){
		remove( "USB:/apps/wiicraft/icon.png" );
	}
	
	// Open file
	FILE *f2;
	if(fatDevice == FAT_DEVICE_SD){
		f2=fopen("sd:/apps/wiicraft/icon.png", "wb");
	}
	else{
		f2=fopen("USB:/apps/wiicraft/icon.png", "wb");
	}
	
	// If file can't be created
	if (f == NULL) {
		fclose(f);
		die("There was a problem creating/accessing the temp file.\n");
	}
	
	printf("Downloading Update");
	
	strcpy(http_request,"GET /wiicraft/icon.png");
	strcat(http_request, " HTTP/1.0\r\nHost: minepocket.azurewebsites.ne\r\n\r\n");
	
	write_http_reply(main_server, http_request); // Send the HTTP message
	result = request_file(main_server, f); // Store the servers reply in our file pointer

	fclose(f2);
	net_close(main_server);
	
	if (result == true) {
		printf("\n\nSuccessfully downloaded the PNG File.\n");
	}
	else {
		die("\n\nDownload of PNG file failed.\n");
	}
	usleep(5000000);
	return;
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
inline void clear(){
	printf("\x1b[2J");   // Clear
	printf("\x1b[2;0H"); // Reset cursor position
}
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
void downloadLauncher(){
	printf("Attempting to connect to server...\n");
	s32 main_server = server_connect();
	printf("Connection established.\n\n");
	
	if(fatDevice == FAT_DEVICE_SD){
		remove( "sd:/apps/wiicraft/boot.dol" );
	}
	else if(fatDevice == FAT_DEVICE_USB){
		remove( "USB:/apps/wiicraft/boot.dol" );
	}
	
	// Open file
	FILE *f;
	if(fatDevice == FAT_DEVICE_SD){
		f=fopen("sd:/apps/wiicraft/boot.dol", "wb");
	}
	else{
		f=fopen("USB:/apps/wiicraft/boot.dol", "wb");
	}
	
	// If file can't be created
	if (f == NULL) {
		fclose(f);
		die("There was a problem creating/accessing the temp file.\n");
	}
	
	printf("Downloading New Launcher...");
	
	char http_request[1000];
	strcpy(http_request,"GET /wiicraft/Launcher.dol");
	strcat(http_request, " HTTP/1.0\r\nHost: minepocket.azurewebsites.ne\r\n\r\n");
	
	write_http_reply(main_server, http_request); // Send the HTTP message
	int result = request_file(main_server, f); // Store the servers reply in our file pointer

	fclose(f);
	net_close(main_server);
	
	if (result == true) {
		printf("\n\nSuccessfully downloaded the new Launcher.\n");
	}
	else {
		die("\n\nDownload of new Launcher failed.\n");
	}
	clear();
	return;
}