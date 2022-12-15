
/*
 * CS354: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>


#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>

#include "command.h"


#include "command.h"

SimpleCommand::SimpleCommand()
{
	// Creat available space for 5 arguments
	_numberOfAvailableArguments = 5;
	_numberOfArguments = 0;
	_arguments = (char **) malloc( _numberOfAvailableArguments * sizeof( char * ) );
}

void
SimpleCommand::insertArgument( char * argument )
{
	if ( _numberOfAvailableArguments == _numberOfArguments  + 1 ) {
		// Double the available space
		_numberOfAvailableArguments *= 2;
		_arguments = (char **) realloc( _arguments,
				  _numberOfAvailableArguments * sizeof( char * ) );
	}
	
	_arguments[ _numberOfArguments ] = argument;

	// Add NULL argument at the end
	_arguments[ _numberOfArguments + 1] = NULL;
	
	_numberOfArguments++;
}

Command::Command()
{
	// Create available space for one simple command
	/// momkwen tzwd
	_numberOfAvailableSimpleCommands = 1;
	_simpleCommands = (SimpleCommand **)
		malloc( _numberOfSimpleCommands * sizeof( SimpleCommand * ) );

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
}

void
Command::insertSimpleCommand( SimpleCommand * simpleCommand )
{
	if ( _numberOfAvailableSimpleCommands == _numberOfSimpleCommands ) {
		_numberOfAvailableSimpleCommands *= 2;
		_simpleCommands = (SimpleCommand **) realloc( _simpleCommands,
			 _numberOfAvailableSimpleCommands * sizeof( SimpleCommand * ) );
	}
	
	_simpleCommands[ _numberOfSimpleCommands ] = simpleCommand;
	_numberOfSimpleCommands++;
}

void
Command:: clear()
{
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		for ( int j = 0; j < _simpleCommands[ i ]->_numberOfArguments; j ++ ) {
			free ( _simpleCommands[ i ]->_arguments[ j ] );
		}
		
		free ( _simpleCommands[ i ]->_arguments );
		free ( _simpleCommands[ i ] );
	}

	if ( _outFile ) {
		free( _outFile );
	}

	if ( _inputFile ) {
		free( _inputFile );
	}

	if ( _errFile ) {
		free( _errFile );
	}

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
}

void
Command::print()
{
	printf("\n\n");
	printf("              COMMAND TABLE                \n");
	printf("\n");
	printf("  #   Simple Commands\n");
	printf("  --- ----------------------------------------------------------\n");
	
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		printf("  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numberOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
		_inputFile?_inputFile:"default", _errFile?_errFile:"default",
		_background?"YES":"NO");
	printf( "\n\n" );
	
}
void handle_sigint(int sig){
	printf("--still working on MYSHELL :D--\n");
	Command::_currentCommand.clear();
	Command::_currentCommand.prompt();
	//Command::clear();
	//printf("myshell>");
	//fflush(stdout);
	//Command::prompt();
}
void handle_sigchld(int sig){
	printf("inside sigchld\n");
	//int child_pid;
	//int status;
	//child_pid=waitpid(-1,&status,WUNTRACED|WNOHANG);
	//if(child_pid==0){
	//int file=open("logfile.txt",O_RDWR | O_CREAT,0777);
	FILE *filepointer=fopen("logfile.txt","ab+");
	//
	time_t t;
	time(&t);
	
	fprintf(filepointer,"--------------------------\n");
	//fprintf(filepointer,"the process of id = %d",getpid());
	fprintf(filepointer," The termination time is  %s",ctime(&t));
	fclose(filepointer);//}
	Command::_currentCommand.clear();
	Command::_currentCommand.prompt();
}
void
Command::execute()
{
	// Don't do anything if there are no simple commands
	if ( _numberOfSimpleCommands == 0 ) {
		prompt();
		return;
	}


	int defaultin = dup( STDIN_FILENO ); // Default file Descriptor for stdin
	int defaultout = dup( STDOUT_FILENO ); // Default file Descriptor for stdout
	int defaulterr = dup( STDERR_FILENO ); // Default file Descriptor for stderr
    

	// Print contents of Command data structure
	print();


//O_APPEND


	// Add execution here
	// For every simple command fork a new process
	// Setup i/o redirection
	// and call exec
	



int pipes[_numberOfSimpleCommands][2];
int myinput=open(_inputFile,O_RDWR  ,0777);
int outfd = open(_outFile,O_RDWR | O_CREAT ,0777);
int append=open(_appendFile,O_APPEND | O_CREAT,0777); 

if(!strcmp("exit",_simpleCommands[0]->_arguments[0]) ||!strcmp("Exit",_simpleCommands[0]->_arguments[0]) || !strcmp("EXIT",_simpleCommands[0]->_arguments[0]))
		{printf("Good Bye!\n");
		exit(1);
		}
int flag=0;


if( strcmp(_simpleCommands[0]->_arguments[0] , "cd") == 0 ){
 char k[100];
//printf("hany1\n");
//printf("getcwd555afterrr======%s\n",getcwd(k,100));
		if(_simpleCommands[0]->_arguments[1] ==NULL){
         //		printf("hany2\n");
	//	printf("getcwd555afterrr======%s\n",getcwd(k,100));
                	chdir("/home");
                }else{
                		//printf("hany3\n");
                	int r=chdir(_simpleCommands[0]->_arguments[1]);
                	if(r!=0){
					perror("error!!");
				}
            flag=1;
                	
                }
              // print();
                clear();
               prompt();
               return;
	}
  

for(int i=0;i<_numberOfSimpleCommands;i++)
{
	
	pipe(pipes[i]);
	
	if(i==0)
	{
 		if(_inputFile)
      		{
       		//int myinput=open(_inputFile,O_RDWR ,0777);
       		dup2(myinput,0);
      		close(myinput);
      		}
      		 else
     		 {
     		 dup2(defaultin,0);
     		 }
	}
	else
	{
 		dup2(pipes[i-1][0],0);
 		close(pipes[i-1][0]);
	}
	if(i==_numberOfSimpleCommands-1)
	{
	    	 if(_outFile)
      		 {
      			//int outfd = open(_outFile,O_RDWR | O_CREAT ,0777);
       			dup2(outfd,1);  
       			//close(outfd);
     		 }
     		 else if(_appendFile)
     		 {
     		 dup2(append,1); 
     		 
     		 }
     		 
     		 else
     		 {
     			 dup2(defaultout,1);
     		 }	
	}
	else
	{
		dup2(pipes[i][1],1);
 		close(pipes[i][1]);
	}
	
	pid_t pid=fork();
	if(pid==0)
	{
	execvp(_simpleCommands[ i ]->_arguments[0] ,_simpleCommands[ i ]->_arguments );
	perror( "ERROR!! \n");
        }
        else
        {
      //  close(outfd);
      //	close(myinput);
        dup2( defaultin, 0 );
	dup2( defaultout, 1 );
	//dup2( defaulterr, 2 );
        if(!_background)
        waitpid(pid,NULL,0);
        }
}


	/* pid_t pid=fork();
        if(pid==0){
        
      
      if(_outFile)
      {
      int outfd = open(_outFile,O_RDWR | O_CREAT ,0777);
       dup2(outfd,1);  
     }
 
      if(_inputFile)
      {
       int myinput=open(_inputFile,O_RDWR ,0777);
       dup2(myinput,0);
      }
      
        // printf("skahkjsadhfgsdhgfhadsk");
        //printf(" tarsh ahany --%s",_simpleCommands[ 0 ]->_arguments[0]);
	//execvp(_simpleCommands[ 0 ]->_arguments[0] ,_simpleCommands[ 0 ]->_arguments );
	perror( "ERROR!! \n");
        }
        
        else 
        {
        if(!_background)
        waitpid(pid,NULL,0);
        }
        
        close( defaultin );
	close( defaultout );
	close( defaulterr );
        */
        dup2( defaultin, 0 );
	dup2( defaultout, 1 );
	dup2( defaulterr, 2 );

	// Clear to prepare for next command
	clear();
	signal(SIGCHLD,&handle_sigchld);
	
	// Print new prompt
	prompt();
}

// Shell implementation
void
Command::prompt()
{
	printf("myshell>");
	fflush(stdout);
}

Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;

int yyparse(void);

int 
main()
{
	Command::_currentCommand.prompt();
	signal(SIGINT,&handle_sigint);
	yyparse();
	return 0;
}

