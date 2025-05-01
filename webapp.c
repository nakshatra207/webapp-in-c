#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void send_response(int client_fd, const char *body) {
    char header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    write(client_fd, header, strlen(header));
    write(client_fd, body, strlen(body));
}

void route(int client_fd, const char *request) {
    if (strstr(request, "GET / ") != NULL) {
        const char *home =
            "<html><body><h1>🎮 Mini Games in C</h1><ul>"
            "<li><a href='/games/tictactoe'>Tic Tac Toe</a></li>"
            "<li><a href='/games/rps'>Rock Paper Scissors</a></li>"
            "<li><a href='/games/guess'>Guess the Number</a></li>"
            "<li><a href='/games/snake'>Snake</a></li>"
            "<li><a href='/games/circle'>Click the Circle</a></li>"
            "<li><a href='/games/quiz'>Math Quiz</a></li>"
            "<li><a href='/games/coin'>Coin Toss</a></li>"
            "<li><a href='/games/color'>Color Match</a></li>"
            "<li><a href='/games/whack'>Whack-a-Mole</a></li>"
            "</ul></body></html>";
        send_response(client_fd, home);
    }

    else if (strstr(request, "GET /games/tictactoe") != NULL) {
        const char *ttt =
            "<html><body><h2>Tic Tac Toe</h2><table id='b' border='1'></table>"
            "<script>let p='X';let b=document.getElementById('b');"
            "for(let i=0;i<3;i++){let r=b.insertRow();"
            "for(let j=0;j<3;j++){let c=r.insertCell();"
            "c.style.width='50px';c.style.height='50px';"
            "c.onclick=()=>{if(!c.textContent){c.textContent=p;p=p==='X'?'O':'X';}}}}"
            "</script><a href='/'>Back</a></body></html>";
        send_response(client_fd, ttt);
    }

    else if (strstr(request, "GET /games/rps") != NULL) {
        const char *rps =
            "<html><body><h2>Rock Paper Scissors</h2>"
            "<button onclick=\"play('rock')\">Rock</button>"
            "<button onclick=\"play('paper')\">Paper</button>"
            "<button onclick=\"play('scissors')\">Scissors</button><p id='res'></p>"
            "<script>function play(u){let c=['rock','paper','scissors'][Math.floor(Math.random()*3)];"
            "let r='';if(u==c)r='Draw';"
            "else if((u=='rock'&&c=='scissors')||(u=='paper'&&c=='rock')||(u=='scissors'&&c=='paper'))"
            "r='You win';else r='Computer wins';"
            "document.getElementById('res').innerText=`Computer chose ${c}. ${r}`;}"
            "</script><a href='/'>Back</a></body></html>";
        send_response(client_fd, rps);
    }

    else if (strstr(request, "GET /games/guess") != NULL) {
        const char *guess =
            "<html><body><h2>Guess the Number (1–10)</h2>"
            "<input id='g' type='number'><button onclick='check()'>Submit</button><p id='f'></p>"
            "<script>let s=Math.floor(Math.random()*10)+1;"
            "function check(){let g=parseInt(document.getElementById('g').value);"
            "document.getElementById('f').innerText=(g===s)?'Correct!':(g<s?'Too low.':'Too high.');}"
            "</script><a href='/'>Back</a></body></html>";
        send_response(client_fd, guess);
    }

    else if (strstr(request, "GET /games/snake") != NULL) {
        const char *snake =
            "<html><body><h2>Snake Game</h2><canvas id='c' width='200' height='200' style='border:1px solid'></canvas>"
            "<script>let x=100,y=100,dx=10,dy=0,ctx=document.getElementById('c').getContext('2d');"
            "document.addEventListener('keydown',e=>{if(e.key=='ArrowRight'){dx=10;dy=0;}if(e.key=='ArrowLeft'){dx=-10;dy=0;}"
            "if(e.key=='ArrowUp'){dx=0;dy=-10;}if(e.key=='ArrowDown'){dx=0;dy=10;}});"
            "setInterval(()=>{ctx.clearRect(0,0,200,200);ctx.fillStyle='green';ctx.fillRect(x,y,10,10);x+=dx;y+=dy;"
            "if(x>=200)x=0;if(x<0)x=190;if(y>=200)y=0;if(y<0)y=190;},150);</script><a href='/'>Back</a></body></html>";
        send_response(client_fd, snake);
    }

    else if (strstr(request, "GET /games/circle") != NULL) {
        const char *circle =
            "<html><body><h2>Click the Circle!</h2><div id='c' style='width:50px;height:50px;border-radius:50%;background:red;position:absolute'></div>"
            "<script>let score=0,div=document.getElementById('c');"
            "function move(){div.style.top=Math.random()*300+'px';div.style.left=Math.random()*300+'px';}"
            "div.onclick=()=>{score++;move();document.title='Score: '+score;};move();</script><a href='/'>Back</a></body></html>";
        send_response(client_fd, circle);
    }

    else if (strstr(request, "GET /games/quiz") != NULL) {
        const char *quiz =
            "<html><body><h2>Math Quiz</h2><p id='q'></p><input id='a'><button onclick='check()'>Check</button><p id='r'></p>"
            "<script>let n1=Math.floor(Math.random()*10),n2=Math.floor(Math.random()*10);"
            "document.getElementById('q').innerText=`What is ${n1} + ${n2}?`;"
            "function check(){let a=document.getElementById('a').value;"
            "document.getElementById('r').innerText=(parseInt(a)==n1+n2)?'Correct!':'Wrong';}</script><a href='/'>Back</a></body></html>";
        send_response(client_fd, quiz);
    }

    else if (strstr(request, "GET /games/coin") != NULL) {
        const char *coin =
            "<html><body><h2>Coin Toss</h2><button onclick='flip()'>Flip</button><p id='r'></p>"
            "<script>function flip(){let r=Math.random()<0.5?'Heads':'Tails';document.getElementById('r').innerText=r;}</script><a href='/'>Back</a></body></html>";
        send_response(client_fd, coin);
    }

    else if (strstr(request, "GET /games/color") != NULL) {
        const char *color =
            "<html><body><h2>Color Match</h2><p id='q'></p><input id='a'><button onclick='check()'>Submit</button><p id='r'></p>"
            "<script>let c=['red','blue','green'][Math.floor(Math.random()*3)];"
            "document.getElementById('q').innerText='Type the color: '+c;"
            "function check(){let a=document.getElementById('a').value;"
            "document.getElementById('r').innerText=(a===c)?'Correct!':'Try again';}</script><a href='/'>Back</a></body></html>";
        send_response(client_fd, color);
    }

    else if (strstr(request, "GET /games/whack") != NULL) {
        const char *whack =
            "<html><body><h2>Whack-a-Mole</h2><div id='g' style='width:300px;height:300px;position:relative;background:#eee'></div><p id='s'>0</p>"
            "<script>let g=document.getElementById('g'),s=0;"
            "function spawn(){let m=document.createElement('div');"
            "m.style.width='30px';m.style.height='30px';m.style.background='brown';m.style.position='absolute';"
            "m.style.top=Math.random()*270+'px';m.style.left=Math.random()*270+'px';"
            "m.onclick=()=>{s++;document.getElementById('s').innerText=s;m.remove();};g.appendChild(m);"
            "setTimeout(()=>m.remove(),1000);}"
            "setInterval(spawn,1000);</script><a href='/'>Back</a></body></html>";
        send_response(client_fd, whack);
    }

    else {
        char *nf = "HTTP/1.1 404 Not Found\r\n\r\n404 - Not Found";
        write(client_fd, nf, strlen(nf));
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    char buffer[4096];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 5);
    printf("🎮 Game server running at http://localhost:%d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&addr, &addrlen);
        int len = read(client_fd, buffer, sizeof(buffer) - 1);
        buffer[len] = 0;

        route(client_fd, buffer);
        close(client_fd);
    }

    return 0;
}

