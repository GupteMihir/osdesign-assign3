package osassign2;
//Mathew Vassair and Mihir Gupte
import java.net.*;
import java.io.*;
import java.util.Arrays;

//The client program for connecting to the echo server for Assignment 2
public class EchoClient {

	//EchoClient's constructor. Call with hostname and port number
	//Also contains the client's echo loop.
	public EchoClient(String host, int port){
		
		//Using try-with-resources to set up the socket and data streams
		try(Socket sock = new Socket(host, port);
			InputStream in = sock.getInputStream();
			InputStream sysIn = System.in; //This might not be good practice
			OutputStream out = sock.getOutputStream();)
		{
			byte[] outBuff = new byte[140];
			byte[] inBuff = new byte[140];
			//Loop until -1 bytes are read, signaling EOF
			while (sysIn.read(outBuff) > -1){
				//or break the loop if 
				if (outBuff[0] == '.')
					break;
				//If not breaking the loop, send the input line to the server, flush the buffer, and read in the response
				else{
					out.write(outBuff);
					out.flush();
					in.read(inBuff);
					//Print the echoed message as though it were a string, also replace \ with / in case some escape shenanigans happen
					System.out.println("Server: " + new String(inBuff).trim().replace('\\', '/'));
					//Zero out the buffers to make sure nothing accidentally gets re-sent
					Arrays.fill(outBuff, (byte)0);
					Arrays.fill(inBuff, (byte)0);
				}
			}
		}catch (IOException e){
			System.out.println("Server not available or bad socket");
			e.printStackTrace();
		}
	}
		
	//Main method for running the EchoClient
	public static void main(String[] args) {
		if (args.length == 2){
			String host = args[0];
			int port = 0;
				try {
					port = Integer.parseInt(args[1]);
				}catch(NumberFormatException e){
					System.out.println("Usage: java EchoClient <host> <port>");
				}
			new EchoClient(host, port);
		} else
			System.out.println("Usage: java EchoClient <host> <port>");
	}

}
