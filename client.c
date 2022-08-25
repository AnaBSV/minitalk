/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sous <ade-sous@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 20:25:03 by ade-sous          #+#    #+#             */
/*   Updated: 2022/08/25 00:13:54 by ade-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
void message(int sig)
{
  printf("%d", sig);
  printf("mensagem enviada com sucesso!\n");
}

void sendchar(int pid, char c)
{
  int i;
  int bit;

  i = 0;

  while (i < 8)
  {
    bit = ((1 << (7 - i)) & c);
    if (bit)
      kill(pid, SIGUSR1);
    else
      kill(pid, SIGUSR2);
    i++;
    usleep(250);
  }
}

int main(int argc, char **argv)
{
  int pid;
  struct sigaction act;
  
  if (argc == 3)
  {
    pid = atoi(argv[1]);
    while(*argv[2])
    {
      sendchar(pid, *argv[2]);
      argv[2]++;
    }
    sendchar(pid, 0);

    // signal(SIGUSR2, message);
  }
  
  
  return (0);
}