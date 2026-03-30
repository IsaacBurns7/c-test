//stack data structure
struct {
	int* arr; 
	int size;
	int cap; 
} Stack;
//block signals -> save oldset 
void block_signals(sigset_t *oldset){
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, oldset);
}
//unblock signals -> reinstate oldset 
void unblock_signals(sigset_t *oldset){
	sigprocmask(SIG_SETMASK, oldset, NULL);
}
//init 
	//init stack w/ malloc - do I need to block?
void stack_init(Stack *s){
	//block?
	s->capacity = 4;
	s->size = 0;
	s->data = (int*) malloc(s->capacity * sizeof(int)); 
}
//push 
	//push onto stack according to size
	//if above cap, resize with realloc
	//block signals

//pop 
	//pop from stack, remember to return -1 if size is 0 
	//write to input int *out
	//block signals 
//peek 
	//access top element, return -1 if fail. 
	//write to input int *out 
	//block 
//is_empty
	//check is size is 0 - do I need to block ? 

//free 
	//free data(do i have to block?)


//rigorous testing 
//maybe add to my github or whatever 
