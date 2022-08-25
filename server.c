/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sous <ade-sous@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:23:57 by ade-sous          #+#    #+#             */
/*   Updated: 2022/08/25 00:16:23 by ade-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void ft_handler(int sig, siginfo_t *info, void *ucontext)
{
  static int i;
  static unsigned char c;

  (void)(ucontext);
  
  if (sig == SIGUSR1)
    c += 1 << (7 - i);

  i++;
  if (i == 8)
  {
    i = 0;
    if (c != 0)
      write(1, &c, 1);
    else
      printf("\n client pid: %d \n", info->si_pid);
      // kill(info->si_pid, SIGUSR2);
      
    c = 0;
  }
}
int main(void)
{
  struct sigaction act;

  act.sa_sigaction = ft_handler;
  act.sa_flags = SA_SIGINFO;
  sigaction(SIGUSR1, &act, NULL);
  sigaction(SIGUSR2, &act, NULL);

  printf("PID: %d \n", getpid());

  while(1)
  {
    pause();
  }

  return(0);
}