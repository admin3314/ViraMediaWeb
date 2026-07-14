#include "WebUI.h"

WebUI::WebUI() {
    _server = nullptr;
}

void WebUI::begin() {
   
}

void WebUI::attach(AsyncWebServer *server) {

    _server = server;

    setupRoutes();
}

void WebUI::setupRoutes() {

    if (!_server) return;

    _server->on("/vfm", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send(200, "text/html", getIndexPage());
    });

}


String WebUI::getIndexPage() {

    String html = R"rawliteral(

      <!DOCTYPE html>
      <html>
      <head>
      <meta charset="UTF-8">
      <title>ViraMediaWeb PRO</title>

      <style>
      body {
          font-family: Arial;
          background: #0f0f0f;
          color: #fff;
          margin: 0;
      }

      .header {
          background: #1c1c1c;
          padding: 10px;
          text-align: center;
          font-size: 20px;
      }

      .container {
          width: 95%;
          margin: auto;
      }

      .panel {
          background: #1e1e1e;
          margin: 10px 0;
          padding: 15px;
          border-radius: 10px;
      }

      .dropzone {
          border: 2px dashed #555;
          padding: 25px;
          text-align: center;
          margin: 10px 0;
          color: #aaa;
      }

      .file {
          display: flex;
          justify-content: space-between;
          padding: 8px;
          border-bottom: 1px solid #333;
          align-items: center;
      }

      button {
          padding: 6px 10px;
          border: none;
          cursor: pointer;
          border-radius: 5px;
      }

      .del {
          background: #ff4444;
          color: white;
      }

      .refresh {
          background: #2d89ff;
          color: white;
      }

      img {
          height: 40px;
          margin-right: 10px;
          border-radius: 5px;
      }

#footer{
    width:92%;
    max-width:420px;
    margin:20px auto 10px;
    text-align:center;
    font-size:12px;
    color:#aaa;
    background: rgba(15,15,15,0.6);
    border: 1px solid rgba(255,255,255,0.08);
    backdrop-filter: blur(12px);
    -webkit-backdrop-filter: blur(12px);
    border-radius:14px;
    padding:8px;
    box-shadow: 0 10px 30px rgba(0,0,0,0.6);
}
      a{
          color:#66ccff;
          text-decoration:none;
      }
      a:hover{
          color:#ffffff;
      }


      </style>

      </head>

      <body>

      <div class="header">ViraMediaWeb PRO File Manager</div>

      <div class="container">

      <div class="panel">

      <h3>Upload</h3>

      <div class="panel">
      <h3>Storage</h3>
      <div id="storage"></div>
      </div>

      <div class="dropzone"
          ondrop="dropHandler(event)"
          ondragover="event.preventDefault()">
      Drop file here
      </div>

      <input type="file" id="file">
      <button onclick="upload()">Upload</button>

      </div>

      <div class="panel">

      <h3>Files</h3>

      <button class="refresh" onclick="loadFiles()">Refresh</button>

      <div id="files"></div>

      </div>

      </div>

      <div id="footer">
        <hr style="border:0;border-top:1px solid #444;margin:10px;">
          <div style="text-align:center; font-size:13px; color:#888;">
            Powered By <span style="color:#fff">@viramedar</span><br>
            🔗 
            <a href="#"
                onclick="openYT()"
                target="_blank"
                rel="noopener noreferrer"
                style="color:#ff5555;">
                YouTube
            </a> |
            <a href="#"
                onclick="openTG()"
                target="_blank"
                rel="noopener noreferrer"
                style="color:#55aaff;">
                Telegram
            </a> |
            <a href="#"
                onclick="openIG()"
                target="_blank"
                rel="noopener noreferrer"
                style="color:#ff55ff;">
                Instagram
            </a> |
            <a href="#"
                onclick="openGH()"
                target="_blank"
                rel="noopener noreferrer"
                style="color:#ffffff;">
                GitHub
            </a>
          </div>
        <br>
      </div>

      <script>
        function openYT(){
            window.open("https://youtube.com/@viramedar", "_blank");
        }
        function openTG(){
            window.open("https://t.me/viramedar", "_blank");
        }
        function openIG(){
            window.open("https://instagram.com/viramedar", "_blank");
        }
        function openGH(){
            window.open("https://github.com/admin3314", "_blank");
        }


      async function loadFiles() {

          let res = await fetch('/files');
          let data = await res.json();

          let out = '';

          data.forEach(f => {

              let isImg = f.name.match(/\.(jpg|png|jpeg|gif)$/i);

              out += `
              <div class="file">

                  <div style="display:flex;align-items:center;">
                      ${isImg ? `<img src="/${f.name}">` : ``}
                      <span>${f.name} (${f.size} bytes)</span>
                  </div>

                  <div>
                      <button onclick="viewFile('${f.name}')">View</button>
                      <button class="del" onclick="del('${f.name}')">Delete</button>
                  </div>

              </div>`;
          });

          document.getElementById('files').innerHTML = out;
      }


      function viewFile(name) {
          window.open('/' + encodeURIComponent(name), '_blank');
      }


      async function uploadFile(file) {

          let form = new FormData();
          form.append("file", file);

          await fetch('/upload', {
              method: 'POST',
              body: form
          });

          loadFiles();
      }

      function upload() {
          let file = document.getElementById('file').files[0];
          uploadFile(file);
      }

      function dropHandler(ev) {

          ev.preventDefault();

          let file = ev.dataTransfer.files[0];

          uploadFile(file);
      }

      async function del(name) {

          await fetch('/delete?name=' + name);
          loadFiles();
      }

      loadFiles();

      async function loadStorage() {
          let res = await fetch('/storage');
          let d = await res.json();

          document.getElementById('storage').innerHTML =
              "Total: " + d.total + " bytes<br>" +
              "Used: " + d.used + " bytes<br>" +
              "Free: " + d.free + " bytes";
      }

      loadStorage();

      </script>

      </body>
      </html>

      )rawliteral";

    return html;
}
