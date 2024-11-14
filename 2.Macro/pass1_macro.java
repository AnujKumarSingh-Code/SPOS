import java.io.*;
import java.util.*;

public class pass1_macro {

	public static void main(String[] args) {
		
		FileReader fr = null;
		BufferedReader br =  null;		
		try {
			String inputFile ="input_macro.txt";
			fr = new FileReader(inputFile);
			br = new BufferedReader(fr);
			
			LinkedHashMap<String,Integer> MNT = new LinkedHashMap<String,Integer>();
			ArrayList<LinkedHashMap<String,String>> ALA = new ArrayList<LinkedHashMap<String,String>>();
			ArrayList<String> MDT = new ArrayList<String>();
			
			String ALAoutput = "ALA.txt";
			
			FileWriter f2 = null; 
			BufferedWriter b2 = null; 
			
			f2 = new FileWriter(ALAoutput);
			b2 = new BufferedWriter(f2);
			String sCurrentLine;
			int MNTloc = 0;
			int MDTloc = 0; 
			int isMacro = 0;
			int macroLine = 0 ;
			int start = 0;
			while((sCurrentLine = br.readLine()) != null ) {
			
			String[] s = sCurrentLine.split(" ");
    		
			if(s[1].equals("MACRO") && isMacro == 0 ) {
				isMacro +=1 ;
				macroLine = 1;
				continue;
			}	
            if( isMacro != 0 ) {
            	
            	if(s[1].equals("MACRO")) {
            		
            		MDT.add(sCurrentLine);
            		MDTloc++;
    				isMacro +=1 ;
    				continue;
    			}          		
            	if( s[1].equals("MEND") ) {
            		MDT.add(sCurrentLine);
            		MDTloc++;
            		isMacro -= 1; 
            		if( isMacro == 0) {
            		macroLine = 0;
            		MNTloc++;
            		}
            		continue;
            	}           	
            	if( macroLine == 1 ) {
            	//System.out.println(s[1]+" "+sCurrentLine);
            	MNT.put( s[1] , MDTloc );
            	MDT.add(sCurrentLine);
            	LinkedHashMap<String,String> temp = new LinkedHashMap<String,String>();
            	
            	if( s.length >= 3 ) { 
            	
            	String[] ss = s[2].split("\\,");
            	int n = ss.length; 
            	int alapointer = 0;
            	for( int i = 0 ; i<n; i++ ) {
            	           			
            			String alaput = "#" + String.valueOf(alapointer);
            			
            			if( ss[i].indexOf("=") != -1 ) {
            			ss[i] = ss[i].split("=")[0];
            			}
            			
            			temp.put(alaput,ss[i]);
            			alapointer++;
            	           		
            	}
            	if( temp.isEmpty() ) {
            		ALA.add(null);
            	}
            	else {
            		
            		ALA.add(temp);
            		
                 }
            	
            	}
            	
            	MDTloc++;
            	macroLine++;
            	continue;
            	}
            	else {
            		
            		String mdtput = "";
            		String[] ss = sCurrentLine.split(" |\\,");
            		
            		int n = ss.length; 
            		int op = 0; 
            				
            		for( int i = 0; i<n; i++ ) {		
            			if( i >= 1 && i<=2 ) mdtput += " ";
            			else if( i>2 ) mdtput += ",";
            			
            			op = 0;
            			
            			for (Map.Entry<String,String> m : (ALA.get(MNTloc)).entrySet()) {
            				
            				
    						if (m.getValue().equals(ss[i]) ) {
    							
    							
    							mdtput += m.getKey(); 
    							op = 1; 
    						}
    					}
            			
            			if( op == 0 ) { 
            				mdtput += ss[i];
            			}
            			
            			
            			
            		}
            		
            		MDT.add(mdtput);
            		
            		
            		macroLine++; 
            		MDTloc++;
            		continue;
            		
            	}	
			}

			if( start == 1 ) {
				
				
				if( s[1] == "END" ) {
					start = 0 ; 
					continue;
				}
				int isMacroinprog = 0 ;
				int ifmacrofounditsindinMNT = 0 ;
				int ifmacrofounditsaddinMDT = 0;
				
				for (Map.Entry<String,Integer> m : MNT.entrySet() ) {
					if (m.getKey().equals(s[1]) ) {				
						
						ifmacrofounditsaddinMDT = m.getValue();
						isMacroinprog = 1;
					//	System.out.println("AAAAYYYYEEEAAAHHHH!!!!");	
						break;
						
						
					}
					
					ifmacrofounditsindinMNT++;
				}		
			if( isMacroinprog == 1) {
					
				    String[] s2 = (MDT.get(ifmacrofounditsaddinMDT)).split(" ");
				    ifmacrofounditsaddinMDT++;
				    LinkedHashMap<String,String> ma = new LinkedHashMap<String,String>(); 
				    
				    if( s2.length >= 3 ) {
				    	
					String[] ss = s[2].split("\\,");
				    String[] sss = s2[2].split("\\,");
				    
				    int n = sss.length; 
				    int ml = ss.length;
				    
				    for( int i = 0 ; i<n; i++ ) {
				    	
				    	String tem = "" ;
				    	if( ml==0 ) {
				    		
				    		tem = sss[i].split("\\=")[1];
				    		sss[i] =  sss[i].split("\\=")[0];
				    		
				    	}
				    	else {
				    		
				    		tem = ss[i];
				    		--ml;
				    	
				    	}
				    	for (Map.Entry<String,String> m : (ALA.get(ifmacrofounditsindinMNT)).entrySet() ) {
							if ( m.getValue().equals(sss[i]) ) {				
									ma.put(m.getKey(),tem);								
									sss[i] = tem;
							}
						}
				    }
				    
				    b2.write("ALA for Macro: " + s2[1] + "\n");
				    
				    b2.write( s2[1] + " " );
				    for( int i = 0 ; i<sss.length;  i++  ) {
				    	b2.write(sss[i]);
				    	if( i!= sss.length - 1 ) {
				    		b2.write(",");
				    	}
				    	else {
				    		b2.write("\n");
				    	}
				    }
				    
				    
				    for (Map.Entry<String,String> m : ma.entrySet() ) {
						b2.write( m.getValue() + "\n");
					}
				    
				    b2.write("Expanded Code: "+s2[1]+"\n");
				    }
				    
				    
				    String csCurrentLine;
				    int cisMacro = 0; 
				    int cmacroLine = 0 ;
				    
				    
				    while( isMacroinprog == 1 ) {
				    	
				    	csCurrentLine = MDT.get(ifmacrofounditsaddinMDT);
				    	String[] cs = csCurrentLine.split(" ");
				    	
				    	if(  cs[1].equals("MACRO") && cisMacro == 0) {
				    		
				    	
				    		cisMacro = 1; 
				    		cmacroLine = 1;
				    		ifmacrofounditsaddinMDT++;				    		
				    		continue;
				    	
				    	}
				    	if( cs[1].equals("MEND") && cisMacro==0 ) {
		            		break;
		            	}
				    	
				    	String tput = "";
	            		String[] sts = csCurrentLine.split(" |\\,");
	            		
	            		int n1 = sts.length; 
	            		int op1 = 0; 
	            				
	            		for( int i = 0; i<n1; i++ ) {
	            			
	            			if( i >= 1 && i<=2 ) tput += " ";
	            			else if( i>2 ) tput += ",";
	            			
	            			op1 = 0;
	            			
	            			for (Map.Entry<String,String> m : ma.entrySet()) {
	            				
	    									
	            				if( m.getKey().equals(sts[i])) {
	    	    							tput += m.getValue();
	    	    							
	    	    							op1 = 1; 
	            				}
	    	    						
	    	    					
	    						
	    					}
	            			
	            			if( op1 == 0 ) { 
	            				tput += sts[i];
	            			}
	            			
	            			
	            			
	            		}
	            		b2.write(tput + "\n");
				    	
				    	
				    	if( cisMacro == 1) {	
				    		if( cs[1].equals("MEND") ) {
			            		MDT.add(csCurrentLine);
			            		MDTloc++;
			            		cisMacro = 0; 
			            		cmacroLine = 0;
			            		MNTloc++;
			            		break;
			            	}
				    		
				    	if( cmacroLine == 1) {
				    		
				    		LinkedHashMap<String,String> temp = new LinkedHashMap<String,String>();
				    		
				    		for (Map.Entry<String,String> m : ma.entrySet() ) {
								if ( m.getKey().equals(cs[1]) ) {				
										cs[1] = m.getValue();								
								}
							}
				    		
				    		MNT.put( cs[1] , MDTloc );
				    		int n = cs.length;
				    		String putsinmdt = "";
				    		for( int i = 0; i<n; i++ ) {
				    			
				    			if( i!=0 ) putsinmdt += " ";
				    			putsinmdt += cs[i];
				    		}
			            	MDT.add(putsinmdt);
			            	
			            	if( cs.length >= 3 ) { 
			            	
			            	String[] ss = cs[2].split("\\,");
			            	n = ss.length; 
			            	int alapointer = 0;
			            	for( int i = 0 ; i<n; i++ ) {
			            	           			
			            			String alaput = "#" + String.valueOf(alapointer);
			            			if( ss[i].indexOf("\\=") != -1 ) {
			            			ss[i] = ss[i].split("\\=")[0];
			            			}
			            			temp.put(alaput,ss[i]);
			            			alapointer++;
			            	           		
			            	}
			            	
			            	if( temp.isEmpty() ) {
		                		ALA.add(null);
		                	}
		                	else {
		                		ALA.add(temp);
		                	}
			            	
			            	}
			            	
			            	MDTloc++;
			            	cmacroLine++;
			            	ifmacrofounditsaddinMDT++;
			            	
			            	continue;
				    		
				    		
				    	}
				    	else {
				    		
				    		String mdtput = "";
		            		String[] ss = csCurrentLine.split(" |\\,");
		            		
		            		int n = ss.length; 
		            		int op = 0; 
		            				
		            		for( int i = 0; i<n; i++ ) {
		            			
		            			if( i >= 1 && i<=2 ) mdtput += " ";
		            			else if( i>2 ) mdtput += ",";
		            			
		            			op = 0;
		            			
		            			for (Map.Entry<String,String> m : (ALA.get(MNTloc)).entrySet()) {
		    						if (m.getValue() == ss[i] ) {				
		    							mdtput += m.getKey();
		    							op = 1; 
		    						}
		    					}
		            			
		            			if( op == 0 ) { 
		            				mdtput += ss[i];
		            			}
		            		}
		            		
		            		MDT.add(mdtput);
		            		
		            		
		            		cmacroLine++; 
		            		MDTloc++;
		            		ifmacrofounditsaddinMDT++;
		            		continue;
				    	}
				    	
				    	}// if cismacro==1;
				    	
				   
				    	ifmacrofounditsaddinMDT++;		
				    } // while loop
				}
				else {
					continue;
				}	
			}
			if( s[1].equals("START") ) {
				start = 1;
				continue;
			}
			}
			
			FileWriter f = null; 
			BufferedWriter b = null; 
			
			String MNToutput = "MNT.txt";
			f = new FileWriter(MNToutput);
			b = new BufferedWriter(f);
			
			ArrayList<String> arr = new ArrayList<String>();
			ArrayList<Integer> arr2 = new ArrayList<Integer>();
			int k=0;
			for (Map.Entry<String,Integer> m : MNT.entrySet() ) {
				b.write(k+"\t\t"+m.getKey() + "\t" + m.getValue()+"\n");
				arr.add(m.getKey());
				arr2.add(m.getValue());
				k++;
				
			}
			
			FileWriter f1 = null; 
			BufferedWriter b1 = null; 
			
			String MDToutput ="MDT.txt" ;
			 f1 = new FileWriter(MDToutput);
			 b1 = new BufferedWriter(f1);
			
			
			int n = MDT.size();
			
			for( int i = 0 ; i<n; i++ ) {
				
				b1.write(i+"\t\t"+MDT.get(i) + "\n");
				
			}
			b2.write("ALA");
			br.close();
			b.close();
			b1.close();
			b2.close();
		}
		 catch ( IOException e) {
			e.printStackTrace();
		}
	}
}


/*### Pass 1 and Pass 2 in Macro Processing

In assembly language programming, macros simplify repetitive code by defining a sequence of instructions that can be reused. Macros are processed by a **macro processor**, which generally performs the following tasks:
- Expanding macros wherever they are used in the code.
- Replacing macro names with corresponding code sequences.
  
The macro processing is typically done in **two passes**: Pass 1 and Pass 2. These passes handle tasks like macro definition storage, parameter substitution, and expansion, which together allow macros to be incorporated into the final assembly code.

---

### Pass 1: Macro Definition Analysis

**Purpose**: Pass 1 focuses on analyzing and defining macros without expanding them. It builds a definition table to store information about macros for efficient processing in Pass 2.

#### Key Objectives of Pass 1:
1. **Identifying Macros**:
   - The assembler scans the source code to detect macro definitions. A macro definition typically starts with a `MACRO` keyword and ends with an `MEND` keyword.
  
2. **Storing Macro Definitions**:
   - Macro definitions, parameters, and sequences of instructions are stored in a **Macro Definition Table (MDT)** and **Macro Name Table (MNT)**.
   - The **MDT** stores the actual lines of code within each macro, while the **MNT** holds macro names and points to the corresponding entry in the MDT.

3. **Handling Parameters**:
   - During Pass 1, any parameters in the macro definition are stored and labeled as placeholders (e.g., `&ARG1`, `&ARG2`).
   - A **Keyword Parameter Table (KPT)** may also be used to keep track of default values for parameters, allowing flexibility in macro calls.

4. **Defining Expansion Data Structures**:
   - Pass 1 creates data structures necessary for expansion in Pass 2. Commonly used structures include:
     - **MDT**: Stores each macro’s line of code and instructions.
     - **MNT**: Points to the start of each macro in the MDT.
     - **ALA (Argument List Array)**: Tracks parameters used in macro calls.

#### Example of Pass 1:
Given the macro definition:
```assembly
MACRO
INCR &ARG1, &ARG2=5
A 1, &ARG1
ADD &ARG2, &ARG1
MEND
```

In Pass 1:
- `MNT` will store `INCR` with a pointer to its definition in the `MDT`.
- `MDT` will hold the lines for `A 1, &ARG1` and `ADD &ARG2, &ARG1`.
- `ALA` will map `&ARG1` and `&ARG2`.

#### Output of Pass 1:
Pass 1 generates an intermediate table (MDT and MNT), which serves as input for Pass 2. No actual code expansion is done in this phase; instead, it only defines structures for later expansion.

---

### Pass 2: Macro Expansion

**Purpose**: Pass 2 expands macros wherever they are called, using information from the tables created in Pass 1. This is the phase where macros are replaced by actual assembly code, making the program fully executable.

#### Key Objectives of Pass 2:
1. **Processing Macro Calls**:
   - The assembler goes through the source code to locate macro calls. When a macro call is found, it uses the MNT to find the start of the macro in the MDT.

2. **Parameter Substitution**:
   - The ALA (Argument List Array) maps actual parameters passed during macro calls to the formal parameters defined in Pass 1.
   - Pass 2 substitutes these actual parameters into the macro body (from the MDT), creating expanded code that includes specific values.

3. **Generating Expanded Code**:
   - For each macro invocation, the assembler copies the instructions from the MDT, substituting actual arguments where needed, and adds this expanded code to the final output.
   - If default values were defined for parameters in Pass 1, Pass 2 uses these defaults unless overridden by actual arguments in the macro call.

#### Example of Pass 2:
Using the previous macro definition, suppose the following macro call appears:
```assembly
INCR B, 10
```

In Pass 2:
- The `ALA` is updated to map `&ARG1` to `B` and `&ARG2` to `10`.
- The MDT entries are used to generate:
  ```assembly
  A 1, B
  ADD 10, B
  ```

#### Output of Pass 2:
The final output of Pass 2 is the fully expanded source code with all macros replaced by their corresponding instructions. This expanded code is then ready for further assembly into machine code.

---

### Detailed Data Structures in Macro Processing

1. **Macro Definition Table (MDT)**:
   - Stores each line of the macro’s code, with placeholders for parameters.
   - Each macro is entered sequentially, and a pointer to each macro’s start is stored in the MNT.

2. **Macro Name Table (MNT)**:
   - Lists macro names and pointers to their definitions in the MDT, allowing quick access to the macro's code.
   
3. **Argument List Array (ALA)**:
   - Stores actual arguments passed to macros.
   - Each macro invocation has a unique ALA entry to map its actual arguments to the formal parameters.

---

### Comparison of Pass 1 and Pass 2

| Aspect                | Pass 1                                      | Pass 2                           |
|-----------------------|---------------------------------------------|----------------------------------|
| **Purpose**           | Define macros and store in tables           | Expand macros into full code     |
| **Parameter Handling**| Create placeholders in MDT and ALA          | Replace placeholders with values |
| **Output**            | MDT, MNT, and ALA tables                    | Fully expanded source code       |
| **Macro Expansion**   | No                                          | Yes                              |

---

### Possible Viva Questions

1. **What is the purpose of Pass 1 in macro processing?**
   - Pass 1 is for analyzing and defining macros, creating tables that store macro information without expanding them.

2. **How does Pass 1 handle macro parameters?**
   - Pass 1 identifies parameters and stores them in placeholders within the MDT, mapping them to indices in the ALA.

3. **What data structures are commonly used in macro processing?**
   - Key structures include the MDT, MNT, and ALA, which store macro definitions, names, and parameter mappings.

4. **What is the purpose of Pass 2 in macro processing?**
   - Pass 2 performs macro expansion, replacing macro calls with their corresponding code sequences using the definitions from Pass 1.

5. **How does the macro processor handle default parameters?**
   - Default parameters are stored during Pass 1, and if no actual argument is provided in the call, Pass 2 uses the default values.

6. **What would happen if there was only one pass in the macro processor?**
   - A single pass would complicate handling multiple macro invocations and redefinitions, as macros need to be fully defined before they can be expanded.

7. **How does the macro processor differentiate between a macro definition and a macro call?**
   - The processor detects the `MACRO` and `MEND` keywords for definitions, while macro calls are recognized based on the names listed in the MNT.

8. **What is the role of the ALA in macro processing?**
   - The ALA maps actual parameters to formal ones, allowing parameter substitution during macro expansion.

9. **Why is a two-pass approach generally used for macro processing?**
   - The two-pass approach simplifies handling nested macros, default arguments, and multiple invocations by separating definition from expansion.

10. **Can nested macros be expanded in this system?**
    - Yes, but additional handling is required to resolve inner macros during Pass 2 expansion, ensuring correct substitution.

This two-pass approach to macro processing optimizes macro handling by clearly separating definition and expansion phases, resulting in structured, maintainable, and efficient assembly code.*/

/*The two codes you've shared are Java programs that implement **Pass 1** and **Pass 2** of macro processing in a two-pass assembler. Below is a detailed explanation of how each pass works:

### Pass 1 - Macro Definition Processing

**Objective**: Pass 1 of the macro processor reads the input and identifies macros, creating the following tables:
1. **Macro Name Table (MNT)** - Stores macro names along with a pointer to their definitions in the Macro Definition Table (MDT).
2. **Macro Definition Table (MDT)** - Holds the actual macro definitions, with placeholders for arguments.
3. **Argument List Array (ALA)** - Used to replace positional arguments with actual parameters when the macro is invoked.

**Code Breakdown**:
1. **File Reading**:
   - The code reads a file named `input_macro.txt`, which contains assembly code with macro definitions and invocations.

2. **Data Structures**:
   - `MNT`: A `LinkedHashMap` that maps macro names to their start location in `MDT`.
   - `ALA`: An `ArrayList` of `LinkedHashMap`, where each `LinkedHashMap` holds the parameters for a specific macro.
   - `MDT`: An `ArrayList` storing the lines of each macro definition.

3. **Macro Processing Logic**:
   - When `MACRO` is encountered in a line, `isMacro` is set to indicate macro processing. The following lines are part of the macro definition until `MEND` is found.
   - The first line after `MACRO` is the macro name, added to `MNT` with its starting location in `MDT`.
   - **Parameters Handling**:
     - The parameters for the macro are parsed and stored in `ALA`. Each parameter is assigned a placeholder like `#0`, `#1`, etc., which are used in the macro definition.
   - For each line in the macro, parameters are replaced with their corresponding placeholders from `ALA` and stored in `MDT`.
   - When `MEND` is encountered, it signals the end of the macro, and the process repeats for the next macro.

4. **Output**:
   - The `MNT`, `MDT`, and `ALA` are written to files: `MNT.txt`, `MDT.txt`, and `ALA.txt`, respectively.

### Pass 2 - Macro Expansion Processing

**Objective**: Pass 2 of the macro processor expands macros by replacing each macro call with the appropriate code from `MDT`, using `ALA` for argument substitution.

**Code Breakdown**:
1. **Data Structures**:
   - The `output` `LinkedHashMap` reads expanded macro instances from `ALA.txt`. For each macro invocation, `output` stores the expanded code, read from the ALA file created during Pass 1.

2. **Macro Expansion**:
   - The `output` map holds macro expansions in a reusable form. For each line in `inputmac2.txt`:
     - If a macro name is detected (matching an entry in `output`), it writes the corresponding expanded code to `pass2_output.txt`.
   - Lines outside macros are written directly to the output without modification.

3. **Output**:
   - The output file, `pass2_output.txt`, contains the final assembly code with all macro invocations expanded.

### Summary of Pass 1 and Pass 2 Workflow

1. **Pass 1**:
   - Parses and stores macro definitions in `MDT`.
   - Creates an `ALA` for handling parameters.
   - Records each macro name in `MNT` with its location in `MDT`.

2. **Pass 2**:
   - Expands each macro invocation using the `output` map from `ALA`.
   - Writes the final expanded assembly code to `pass2_output.txt`.

This macro processor effectively demonstrates two-pass processing, where Pass 1 structures macro data for efficient lookup, and Pass 2 performs actual macro expansions by referencing the data organized in Pass 1. Let me know if you need further clarification on any specific part of the code!*/

