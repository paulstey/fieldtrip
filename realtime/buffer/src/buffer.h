/*
 * Copyright (C) 2008, Robert Oostenveld & Christian Hesse
 * F.C. Donders Centre for Cognitive Neuroimaging, Radboud University Nijmegen,
 * Kapittelweg 29, 6525 EN Nijmegen, The Netherlands
 *
 */

/* prevent double include */
#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "platform_includes.h"
#include "message.h"

#ifndef POLLRDNORM
#define POLLRDNORM POLLIN
#endif

#ifndef POLLRDBAND
#define POLLRDBAND POLLPRI
#endif

#ifndef POLLWRNORM
#define POLLWRNORM POLLOUT
#endif

#ifndef POLLWRBAND
#define POLLWRBAND POLLOUT
#endif

#define BACKLOG           16
#define DEFAULT_HOSTNAME "localhost"
#define DEFAULT_PORT      1972

#define SO_RCVBUF_SIZE 16384
#define SO_SNDBUF_SIZE 16384

/* this is because the function  has been renamed, but is perhaps already in use in other software */
#define open_remotehost open_connection

/* FIXME these should be variable */
#define MAXNUMBYTE      (512*1024*1024)
#define MAXNUMSAMPLE    600000
#define MAXNUMEVENT     100
#define MAXNUMPROPERTY  100

#define WRAP(x,y) ((x) - ((int)((float)(x)/(y)))*(y))
#define FREE(x) {if (x) {free(x); x=NULL;}}

#ifdef __cplusplus
extern "C" {
	
#endif

/* declaration of "public" buffer API functions */
int read_header( const char *hostname, int port,           void **ppw);
int read_data(   const char *hostname, int port, int *pnw, void **ppw);
int read_event(  const char *hostname, int port, int *pnw, void **ppw);
int write_header(const char *hostname, int port,           void **ppw);
int write_data(  const char *hostname, int port, int *pnw, void **ppw);
int write_event( const char *hostname, int port, int *pnw, void **ppw);
int flush_header(const char *hostname, int port);
int flush_data(  const char *hostname, int port);
int flush_event( const char *hostname, int port);
void cleanup_buffer();

/* definition of the functions that implement the network transparent server */
void *tcpserver(void *);
void *tcpsocket(void *);

/* definition of test functions that emulate an acquisition system */
void *sinewave_thread(void *);
void *event_thread(void *);

/* definition of the functions used in thread cancelation, see cleanup.c */
void cleanup_message(void **arg);
void cleanup_header(void **arg);
void cleanup_data(void **arg);
void cleanup_event(void **arg);
void cleanup_property(void **arg);
void cleanup_buf(void **arg);
void cleanup_socket(int *);

/* definition of helper functions for debugging and printing the content of various structures */
void print_request(messagedef_t *);
void print_response(messagedef_t *);
void print_headerdef(headerdef_t *);
void print_datadef(datadef_t *);
void print_eventdef(eventdef_t *);
void print_propertydef(propertydef_t *);
void print_datasel(datasel_t *);
void print_eventsel(eventsel_t *);
void print_propertydef(propertydef_t *);
void print_buf(void *, int);

/* definition of even more helper functions, see util.c */
int open_connection(const char*, int);
int close_connection(int);
int append(void **, int, void *, int);
int bufread(int, void *, int);
int bufwrite(int, const void *, int);
int clientrequest(int, message_t *, message_t**);
int dmarequest(const message_t *, message_t**);
int tcprequest(int, const message_t *, message_t**);
int find_property(property_t *);
int get_property(int, const char *, INT32_T *);
int set_property(int, const char *, INT32_T *);
void check_datatypes(void);

typedef struct {
	char name[256];
	int  port;
} host_t;

#ifdef __cplusplus
}
#endif

#endif

