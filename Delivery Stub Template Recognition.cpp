//Delivery Stub Image Recognition.cpp
#include <cekeikon.h>
int main(int argc, char** argv) {
	if (argc!=3) {
		printf("ep input.jpg output.png \n");
		erro("Error: Invalid Arguments Input");
	}
	Mat_<FLT> a; le(a,argv[1]);
	Mat_<FLT> m2; le(m2,"m21.pgm");		// raad mx.pgm as floating point 
	Mat_<FLT> m3; le(m3,"m31.pgm");
	Mat_<FLT> m4; le(m4,"m41.pgm");
	
	float media = 0;					// get mean of all matrix pixels
	for(int i = 0; i < a.total(); i++)
		media += a(i)/a.total(); 
	
	Mat_<FLT> cinza(250,1200,media);	 //	increasing margins for optimizing template matching processing 
										// 	the images where centralized in a larger matrix with edge values   
										//	equal to the mean for filtering general noise
										
	
	Mat_<FLT> m2_resized, m2_resized_rodado;	// aux matrices
	Mat_<FLT> m3_resized, m3_resized_rodado;
	Mat_<FLT> m4_resized, m4_resized_rodado;
	
	float mmaior, m2maior, m3maior, m4maior = 0;

	float f1 = 750.0/a.cols;				//	correction fator to convert column number to 750 keeping proportion
	
	Mat_<FLT> a2, melhor, cinza0;
	
	resize(a, a2, Size(0,0), f1, f1, INTER_NEAREST);		// applied correction factor using INTER_NEAREST method  
															// to estimate total column number to be 750
	int ar = (a2.rows-1)/2;
	int br = cinza.rows/2;
	int ac = (a2.cols-1)/2;
	int bc = cinza.cols/2;
	
	float fm, rm;
	int lm, cm, mm;
	
	for (int j=0; j<a2.rows; j++)
				for (int k=0; k<a2.cols; k++)
					cinza(j+br-ar,k+bc-ac) = a2(j,k);			//	centralized read stub matrix on the larger matrix 

	cinza0 = cinza.clone();				
		
	Mat_<FLT> p;
	
	float rodador = -3;		// define starting rotation angle for template matching begin
	
	while(rodador < 3){
		float fator = 0.88;		// define inicial resize factor
		
		while(fator < 1.1){
			resize(m2, m2_resized, Size(0,0), fator, fator, INTER_NEAREST);		// resize m2 stub template 
							
			Mat_<double> m=getRotationMatrix2D(Point2f(m2_resized.cols/2,m2_resized.rows/2), rodador, 1);		// frotate m2 stub template
			warpAffine(m2_resized, m2_resized_rodado, m, m2_resized.size(), INTER_NEAREST, BORDER_CONSTANT, 128.0/255.0);		// dont care pixels on external
																																// image window pixels that
																																// pops up along rotation
			
			float ufa = 0;
			
			for (int j=0; j<cinza.rows; j++)
				for (int k=0; k<cinza.cols; k++)
					ufa += cinza(j,k);
						
			for (int j=0; j<cinza.rows; j++)
				for (int k=0; k<cinza.cols; k++)
					cinza(j,k) = 2*cinza(j,k)/ufa;		// pre processing/ mean correction to keep abs values sum equals to 2
			
			p = matchTemplateSame(cinza, m2_resized_rodado, CV_TM_CCOEFF_NORMED,0.0); // applying template matching function
			
			for (int l=0; l<cinza.rows; l++)
				for (int c=0; c<cinza.cols; c++)	
					if(abs(p(l,c))>m2maior){
						m2maior = abs(p(l,c));
						int w =  l - cinza.rows/2;
						int y =  c - cinza.cols/2;
		
						printf("m2 %f \n", m2maior);
						printf("factor %f \n", fator);
						printf("rotator %f \n", rodador);
						printf("l = %d  c = %d \n\n", w, y);		// shows the higher correlation found along the running program
						
						mmaior = m2maior;
						lm = w;
						cm = y;
						fm = fator;
						rm = rodador;
						mm = 2;
						melhor = m2_resized_rodado;
						
					} 
			fator += 0.001;
		}
		rodador += 0.25;
		
		// printf("rodador %f \n\n", rodador);
	}
	
	rodador = -3;			// repeats the same process for each remaining stub model, always comparing and keeping saved the highest correlations
	
	while(rodador < 3){
		float fator = 0.88;
		
		while(fator < 1.1){
			resize(m3, m3_resized, Size(0,0), fator, fator, INTER_NEAREST);
							
			Mat_<double> m=getRotationMatrix2D(Point2f(m3_resized.cols/2,m3_resized.rows/2), rodador, 1);
			warpAffine(m3_resized, m3_resized_rodado, m, m3_resized.size(), INTER_NEAREST, BORDER_CONSTANT, 128.0/255.0);
			
			float ufa = 0;
			
			for (int j=0; j<cinza.rows; j++)
				for (int k=0; k<cinza.cols; k++)
					ufa += cinza(j,k);
						
			for (int j=0; j<cinza.rows; j++)
				for (int k=0; k<cinza.cols; k++)
					cinza(j,k) = 2*cinza(j,k)/ufa;

			
			p = matchTemplateSame(cinza, m3_resized_rodado, CV_TM_CCOEFF_NORMED,0.0);
			
			for (int l=0; l<cinza.rows; l++)
				for (int c=0; c<cinza.cols; c++)	
					if(abs(p(l,c))>m3maior){
						m3maior = abs(p(l,c));
						int w =  l - cinza.rows/2;
						int y =  c - cinza.cols/2;
		
						printf("m3 %f \n", m3maior);
						printf("factor %f \n", fator);
						printf("rotator %f \n", rodador);
						printf("l = %d  c = %d \n\n", w, y);
						
						if(m3maior > mmaior){
							mmaior = m3maior;
							lm = w;
							cm = y;
							fm = fator;
							rm = rodador;
							mm = 3;
							melhor = m3_resized_rodado;
						}
					} 
			fator += 0.001;
		}
		rodador += 0.25;
		
		// printf("rodador %f \n\n", rodador);
	}
	
	rodador = -3;
	
	while(rodador < 3){
		float fator = 0.88;
		
		while(fator < 1.1){
			resize(m4, m4_resized, Size(0,0), fator, fator, INTER_NEAREST);
							
			Mat_<double> m=getRotationMatrix2D(Point2f(m4_resized.cols/2,m4_resized.rows/2), rodador, 1);
			warpAffine(m4_resized, m4_resized_rodado, m, m4_resized.size(), INTER_NEAREST, BORDER_CONSTANT, 128.0/255.0);
			
			float ufa = 0;
			
			for (int j=0; j<cinza.rows; j++)
				for (int k=0; k<cinza.cols; k++)
					ufa += cinza(j,k);
						
			for (int j=0; j<cinza.rows; j++)
				for (int k=0; k<cinza.cols; k++)
					cinza(j,k) = 2*cinza(j,k)/ufa;

			
			p = matchTemplateSame(cinza, m4_resized_rodado, CV_TM_CCOEFF_NORMED, 0.0);
			
			for (int l=0; l<cinza.rows; l++)
				for (int c=0; c<cinza.cols; c++)	
					if(abs(p(l,c))>m4maior){
						m4maior = abs(p(l,c));
						int w =  l - cinza.rows/2;
						int y =  c - cinza.cols/2;
		
						printf("m4 %f \n", m4maior);
						printf("factor %f \n", fator);
						printf("rotator %f \n", rodador);
						printf("l = %d  c = %d \n\n", w, y);
						
						if(m4maior > mmaior){
							mmaior = m4maior;
							lm = w;
							cm = y;
							fm = fator;
							rm = rodador;
							mm = 4;
							melhor = m4_resized_rodado;
						}
						
					} 
			fator += 0.001;
		}
		rodador += 0.25;
		
		// printf("rodador %f \n\n", rodador);
	}
	
	printf("Highest correlation between %s and m2.pgm: %f \n",argv[1], m2maior);
	printf("Highest correlation between %s and m3.pgm: %f \n",argv[1], m3maior);
	printf("Highest correlation between %s and m4.pgm: %f \n",argv[1], m4maior);
	
	printf("Best fitted template: %d, corr: %f, rotation: %f degrees, factor: %f, desloc(x,y): [%d , %d]",mm, mmaior, rm, fm, cm, lm);
	
	Mat_<COR> d; converte(cinza0,d);		//	creates a painting matrix to highlight the detected stup template
	
	ar = (cinza0.rows-melhor.rows+1)/2;		
	ac = (cinza0.cols-melhor.cols+1)/2;
	
	for (int l=0; l<melhor.rows; l++)		// overlap the highlight recognized stub tamplate painting to the original image
		for (int c=0; c<melhor.cols; c++){
			if(melhor(l,c) == 0.0){
				d(l+ar+lm, c+ac+cm)[0] = 0;			// reduce blue and green levels to zero, highlighting the stub edges -> edges become red
				d(l+ar+lm, c+ac+cm)[1] = 0;
			}
			else{
				d(l+ar+lm, c+ac+cm)[1] = d(l+ar+lm, c+ac+cm)[1]/3;		// reduce red and green leves to 2/3 to highlight grey areas -> becoming bluish
				d(l+ar+lm, c+ac+cm)[2] = d(l+ar+lm, c+ac+cm)[2]/3;
			}
		}

	imp(d,argv[2]); 		// print output image with the detected stub according to the input image name
	
}
