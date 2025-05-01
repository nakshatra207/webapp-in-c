🎮 Mini Games WebApp in Pure C

A lightweight web server written entirely in C that serves a suite of classic browser-based mini-games – no external frameworks, no Node.js, just C and a bit of embedded JavaScript.

🕹️ Included Games

    ✅ Tic Tac Toe

    ✅ Rock Paper Scissors

    ✅ Guess the Number

    ✅ Snake

    ✅ Click the Circle

    ✅ Math Quiz

    ✅ Coin Toss

    ✅ Color Match

    ✅ Whack-a-Mole (basic)

⚙️ How It Works

The server listens on port 8080 and responds to basic HTTP GET requests by serving HTML with inline JavaScript for game logic. All code is written in pure C and uses POSIX sockets.
🚀 Run Locally

gcc webapp.c -o webapp
./webapp

Then open your browser:

👉 http://localhost:8080
