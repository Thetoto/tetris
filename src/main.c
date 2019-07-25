#include "tetris.h"


void sleep_ms(int milliseconds) // cross-platform sleep function
{
#if _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    usleep(milliseconds * 1000);
#endif
}



int main()
{
    int msec = 0;
    int trigger = 250; //milliseconds

    srandom(time(NULL));

    // Open Keyboard
    system("/bin/stty raw"); // To use getchar without pressing Enter
    int flags = fcntl(0, F_GETFL, 0); // Set stdin non blocking
    flags |= O_NONBLOCK;
    fcntl(0, F_SETFL, flags);

    struct game *game = game_init();

    print_map(game->map, game->cur_bloc);
    while (!update(game))
    {
        print_map(game->map, game->cur_bloc);
        clock_t before = clock();
        do
        {
            char in = getchar();
            if (errno == EAGAIN) // Nothing in stdin
            {
                int input = get_input(game, in);
                if (input)
                {
                    print_map(game->map, game->cur_bloc);
                    if(input == 2)
                        break;
                }
            }

            clock_t difference = clock() - before;
            msec = difference * 1000 / CLOCKS_PER_SEC;

        } while (msec < trigger);
    }

    game_destroy(game);
    system("/bin/stty cooked"); // Default mode
    return 0;
}
