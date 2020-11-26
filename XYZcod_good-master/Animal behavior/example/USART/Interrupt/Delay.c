void Delay(unsigned long Time){
	while(Time--);
}
void Delayus(unsigned long Time){
	unsigned long i;
	while(Time--){
		for(i=0;i<11;i++);
	}
}
void Delayms(unsigned long Time){
	unsigned long i;
	while(Time--){
		for(i=0;i<12000;i++);
	}
}
