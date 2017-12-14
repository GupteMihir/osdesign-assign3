package osassign2;
//Mathew Vassair and Mihir Gupte
import java.io.*;
import java.net.Socket;
import java.util.Arrays;

//The EchoSession class, used by the EchoServer to service clients on multiple threads
public class EchoSession implements Runnable {

	//Required variables are defined at the class level to ensure I can access them in run()
	Socket sock;
	InputStream in;
	OutputStream out;
	byte[] buff;

	//Session constructor, is passed a socket and sets up what it needs to run
	public EchoSession(Socket sock){
		this.sock = sock;
		try{
			in = sock.getInputStream();
			out = sock.getOutputStream();
		}catch(IOException e){
			System.err.println("Failed to get socket streams");
			e.printStackTrace();
		}
		buff = new byte[140];
	}

	//Run method which contains the session's loop
	@Override
	public void run() {
		try{
			//Read returns -1 when the session is ended by the client
			while(in.read(buff) > -1){
				out.write(buff);
				out.flush();
				Arrays.fill(buff, (byte)0); //Used to ensure all old data is removed
			}
			
			//Close IO and socket
			in.close();
			out.close();
			sock.close();
		} catch(IOException e){
			System.err.println("An error occured while reading or writing the socket");
			e.printStackTrace();
		}
	}
}
