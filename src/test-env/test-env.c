/*!
    Test to make sure SDL and the environment is setup
*/

#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <stdbool.h>

SDL_Window* win;
SDL_Surface* sur;
SDL_GLContext* con;

void testenv_INIT(){
    SDL_Init(SDL_INIT_EVERYTHING);

    win = SDL_CreateWindow("Test Success ?!?!", 0, 0, 250, 250, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
    );
    if(win == NULL){
        printf("SDL doesn't work, the win == null\n");
        SDL_DestroyWindow(win);
    }

    sur = SDL_GetWindowSurface(win);
    if(sur == NULL){
        printf("SDL doesn't work, sur == null\n");
    }

    // Use OpenGL 3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    con = SDL_GL_CreateContext(win);
}

void glDraw(){
    glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);      
}

void testenv_SDL(){
    int major = -1;
    int minor = -1;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("\n"
           "Vendor:   [%s]\n" 
           "Renderer: [%s]\n"
           "GL Vers:  [%s]\n"
           "GL Shade: [%s]\n"
           "GL Min:   [%d]\n"
           "GL Maj:   [%d]\n"
           ,
        glGetString(GL_VENDOR), 
        glGetString(GL_RENDERER),
        glGetString(GL_VERSION),
        glGetString(GL_SHADING_LANGUAGE_VERSION),
        minor,
        major
    );


    bool done = false;
    SDL_Event event;
    while(!done){
        SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT){
            done = true;
        } else {
            glDraw();
            SDL_GL_SwapWindow(win);      
        }
    }
}

void destroy(){
    SDL_GL_DeleteContext(con);
    SDL_DestroyWindow(win);
}

int main(int argc, char* argv[]){
    testenv_INIT();
    testenv_SDL();
    destroy();

    printf("DONE\n");
}