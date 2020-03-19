/* Step-8 Include required libraries */
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


/* Step-7 Declaration of methods. rules of c programming*/
static char *ngx_http_bismillah(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_bismillah_handler(ngx_http_request_t *r);


/* Step-3: The module directive definition. */
static ngx_command_t ngx_http_bismillah_commands[] = {

    { ngx_string("bismillah"), /* directive name */
      NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS, /* location context and takes no arguments*/
      ngx_http_bismillah, /* configuration setup function */
      0, /* No offset. Only one context is supported. */
      0, /* No offset when storing the module configuration on struct. */
      NULL},

    ngx_null_command /* command termination */
};


/* Step-2: The module context. */
static ngx_http_module_t ngx_http_bismillah_module_ctx = {
    NULL, /* preconfiguration */
    NULL, /* postconfiguration */

    NULL, /* create main configuration */
    NULL, /* init main configuration */

    NULL, /* create server configuration */
    NULL, /* merge server configuration */

    NULL, /* create location configuration */
    NULL /* merge location configuration */
};


/* Step-1: Module definition. The module start from here*/
ngx_module_t ngx_http_bismillah_module = {
    NGX_MODULE_V1,
    &ngx_http_bismillah_module_ctx, /* module context */
    ngx_http_bismillah_commands, /* module directives */
    NGX_HTTP_MODULE, /* module type */
    NULL, /* init master */
    NULL, /* init module */
    NULL, /* init process */
    NULL, /* init thread */
    NULL, /* exit thread */
    NULL, /* exit process */
    NULL, /* exit master */
    NGX_MODULE_V1_PADDING
};


/* Step-6 The bismillah world string. */
static u_char ngx_bismillah_world[] = "Bismillahir Rahmanir Rahim";

/**
 * Step-5
 * Content handler.
 * @param r
 *   Pointer to the request structure. See http_request.h.
 * @return
 *   The status of the response generation.
 */
static ngx_int_t ngx_http_bismillah_handler(ngx_http_request_t *r)
{
    ngx_buf_t *b;
    ngx_chain_t out;

    /* Set the Content-Type header. */
    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char *) "text/plain";

    /* Allocate a new buffer for sending out the reply. */
    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));

    /* Insertion in the buffer chain. */
    out.buf = b;
    out.next = NULL; /* just one buffer */

    b->pos = ngx_bismillah_world; /* first position in memory of the data */
    b->last = ngx_bismillah_world + sizeof(ngx_bismillah_world) - 1; /* last position in memory of the data */
    b->memory = 1; /* content is in read-only memory */
    b->last_buf = 1; /* there will be no more buffers in the request */

    /* Sending the headers for the reply. */
    r->headers_out.status = NGX_HTTP_OK; /* 200 status code */
    /* Get the content length of the body. */
    r->headers_out.content_length_n = sizeof(ngx_bismillah_world) - 1;
    ngx_http_send_header(r); /* Send the headers */

    /* Send the body, and return the status code of the output filter chain. */
    return ngx_http_output_filter(r, &out);
}


/**
 * Step-4 
 * Configuration setup function that installs the content handler.
 * @param cf
 *   Module configuration structure pointer.
 * @param cmd
 *   Module directives structure pointer.
 * @param conf
 *   Module configuration structure pointer.
 * @return string
 *   Status of the configuration setup.
 */
static char *ngx_http_bismillah(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf; /* pointer to core location configuration */
    /* Install the bismillah handler. */
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_bismillah_handler;
    return NGX_CONF_OK;
}