#ifndef HTTSERVER_DEF_HEADER
    #define HTTSERVER_DEF_HEADER
 
    #ifdef __cplusplus
    extern "C" {
    #endif         

    
        #include <stddef.h>   
        struct uws_app_s;
        struct uws_req_s;
        struct uws_res_s;
        typedef struct uws_app_s uws_app_t;
        typedef struct uws_req_s uws_req_t;
        typedef struct uws_res_s uws_res_t;

        uws_app_t *uws_create_app();
        void uws_app_any(uws_app_t *app, const char *pattern, void (*handler)(uws_res_t *, uws_req_t *));
        void uws_app_trace(uws_app_t *app, const char *pattern, void (*handler)(uws_res_t *, uws_req_t *));
        void uws_app_connect(uws_app_t *app, const char *pattern, void (*handler)(uws_res_t *, uws_req_t *));
        void uws_app_head(uws_app_t *app, const char *pattern, void (*handler)(uws_res_t *, uws_req_t *));
        void uws_app_put(uws_app_t *app, const char *pattern, void (*handler)(uws_res_t *, uws_req_t *));
        void uws_app_patch(uws_app_t *app, const char *pattern, void (*handler)(uws_res_t *, uws_req_t *));
        void uws_app_options(uws_app_t *app, const char *pattern, void (*handler)(uws_res_t *, uws_req_t *));
        void uws_app_del(uws_app_t *app, const char *pattern, void (*handler)(uws_res_t *, uws_req_t *));
        void uws_app_post(uws_app_t *app, const char *pattern, void (*handler)(uws_res_t *, uws_req_t *));
        void uws_app_get(uws_app_t *app, const char *pattern, void (*handler)(uws_res_t *, uws_req_t *));
        void uws_app_run(uws_app_t *);
        void uws_app_listen(uws_app_t *app, int port, void (*handler)(void *));
        void uws_res_end(uws_res_t *res, const char *data, size_t length);

     
    #ifdef __cplusplus
    }
    #endif

#endif