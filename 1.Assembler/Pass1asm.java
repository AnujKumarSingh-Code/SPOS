import java.util.*;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter; 
import java.io.IOException;

public class Pass1asm {
	int lc=0;
	int newptr=0,pre=0;
	int libtab_ptr=0,pooltab_ptr=0;
	int symIndex=0,litIndex=0;
	LinkedHashMap<String, Tables> SYMTAB;
	ArrayList<Tables> LITTAB;
	ArrayList<Integer> POOLTAB;
	private BufferedReader br;

	public Pass1asm()
	{
		SYMTAB =new LinkedHashMap<>();
		LITTAB=new ArrayList<>();
		POOLTAB=new ArrayList<>();
		lc=0;
		POOLTAB.add(0);
	}
	public static void main(String[] args) {
		Pass1asm one=new Pass1asm();
		try
		{
			one.parseFile();
		}
		catch (Exception e) {
			System.out.println("Error: "+e); 
		}
	}
	public void parseFile() throws Exception
	{
		String prev="";
		String line,code;
		br = new BufferedReader(new FileReader("input.txt"));
		BufferedWriter bw=new BufferedWriter(new FileWriter("IC.txt"));
		OPtable lookup=new OPtable();
		//bw.write("Intermediate Code\n\n");
		System.out.println("\nIntermediate Code");
		while((line=br.readLine())!=null)
		{
			
			String parts[]=line.split("\\s+");
			if(!parts[0].isEmpty()) //processing of label
			{
				if(SYMTAB.containsKey(parts[0]))
					SYMTAB.put(parts[0], new Tables(parts[0], lc, SYMTAB.get(parts[0]).getIndex()));
				else
					SYMTAB.put(parts[0],new Tables(parts[0], lc, ++symIndex));
			}

			if(parts[1].equals("LTORG") || parts[1].equals("END"))
			{
				int x=libtab_ptr-newptr;
				if(pre!=0 && pre<libtab_ptr ){
				pooltab_ptr++;
				POOLTAB.add(x);}
				pre=libtab_ptr;
				int ptr=POOLTAB.get(pooltab_ptr);
				for(int j=ptr;j<libtab_ptr;j++)
				{
					LITTAB.set(j, new Tables(LITTAB.get(j).getSymbol(),lc));
					code="(DL,02)\t(C,"+LITTAB.get(j).symbol+")";
					bw.write(code+"\n");
					lc++;
				}
				newptr=0;

				if(parts[1].equals("END"))
				{
					code="(AD,02)";
					bw.write(code+"\n");
					break;
				}

			}
			if(parts[1].equals("START"))
			{
				lc=expr(parts[2]);
				code="(AD,01)\t(C,"+lc+")";
				bw.write(code+"\n");
				prev="START";
			}
			
			if(parts[1].equals("ORIGIN"))
			{
				lc=expr(parts[2]);
				if(parts[2].contains("+"))
				{
					//lc=expr(parts[2]);
					String splits[]=parts[2].split("\\+"); //Same for - SYMBOL //Add code
					int x=SYMTAB.get(splits[0]).getAddess()+Integer.parseInt(splits[1]);
					code="(AD,03)\t(C,"+x+")";
					bw.write(code+"\n");
				}
				else if(parts[2].contains("-"))
				{
					
					String splits[]=parts[2].split("\\-"); //Same for - SYMBOL //Add code
					int x=SYMTAB.get(splits[0]).getAddess()-Integer.parseInt(splits[1]);
					code="(AD,03)\t(C,"+x+")";
					bw.write(code+"\n");
				}
				
			}

			//Now for EQU
			if(parts[1].equals("EQU"))
			{
				int loc=expr(parts[2]);
				if(parts[2].contains("+"))
				{
					String splits[]=parts[2].split("\\+");
					int x=SYMTAB.get(splits[0]).getAddess()+Integer.parseInt(splits[1]);
					code="(AD,04)\t(C,"+x+")";

				}
				else if(parts[2].contains("-"))
				{
					String splits[]=parts[2].split("\\-");
					int x=SYMTAB.get(splits[0]).getAddess()-Integer.parseInt(splits[1]);
					code="(AD,04)\t(C,"+x+")";
				}
				else
				{
					code="(AD,04)\t(C,"+Integer.parseInt(parts[2]+")");
				}
				bw.write(code+"\n");
				if(SYMTAB.containsKey(parts[0]))
					SYMTAB.put(parts[0], new Tables(parts[0],loc,SYMTAB.get(parts[0]).getIndex())) ;
				else
					SYMTAB.put(parts[0], new Tables(parts[0],loc,++symIndex));	 
			}

			if(parts[1].equals("DC"))
			{
				lc++;
				int constant=Integer.parseInt(parts[2].replace("'",""));
				code="(DL,02)\t(C,"+constant+")";
				bw.write(code+"\n");
			}
			else if(parts[1].equals("DS"))
			{
				
				int size=Integer.parseInt(parts[2].replace("'", ""));

				code="(DL,01)\t(C,"+size+")";
				bw.write(code+"\n");
				/*if(prev.equals("START"))
				{
					lc=lc+size-1;//System.out.println("here");
					
				}
				else
*/					lc=lc+size;
				prev="";
			}
			if(lookup.getMnemonic(parts[1]).equals("IS"))
			{
				code="(IS,0"+lookup.getOpcode(parts[1])+")\t";
				int j=2;
				String code2="";
				while(j<parts.length)
				{
					parts[j]=parts[j].replace(",", "");
					if(lookup.getMnemonic(parts[j]).equals("RG"))
					{
						code2+="(RG,0"+lookup.getOpcode(parts[j])+")\t";
					}
					else if(lookup.getMnemonic(parts[j]).equals("CC"))
					{
						code2+="(CC,0"+lookup.getOpcode(parts[j])+")\t";
					}
					else
					{
						if(parts[j].contains("="))
						{
							parts[j]=parts[j].replace("=", "").replace("'", "");
							code2+="(L,"+(litIndex)+")";
							LITTAB.add(new Tables(parts[j], -1,++litIndex));
							libtab_ptr++;
							newptr++;
//							code2+="(L,"+(litIndex)+")";
						}
						else if(SYMTAB.containsKey(parts[j]))
						{
							int ind=SYMTAB.get(parts[j]).getIndex();
							code2+= "(S,0"+ind+")"; 
						}
						else
						{
							SYMTAB.put(parts[j], new Tables(parts[j],-1,++symIndex));
							int ind=SYMTAB.get(parts[j]).getIndex();
							code2+= "(S,0"+ind+")";
						}
					}
					j++;
				}
				lc++;
				code=code+code2;
				bw.write(code+"\n");
			}

		}
		bw.close();
		printIC();
		printSYMTAB();
		//Printing Literal table
		PrintLITTAB();
		printPOOLTAB();
	}
	private String x(String string) {
		// TODO Auto-generated method stub
		return null;
	}
	void printIC() throws Exception
	{
		BufferedReader br = new BufferedReader(new FileReader("IC.txt"));
		String line = br.readLine();
		while(line != null)
		{
		  System.out.println(line);
		  line = br.readLine();
		}
		br.close();
	}
	void PrintLITTAB() throws IOException
	{
		BufferedWriter bw=new BufferedWriter(new FileWriter("LITTAB.txt"));
		System.out.println("\nLiteral Table");
		System.out.println("Index\tLiteral\tAddress");
		//bw.write("\nLiteral Table\n");
		//Processing LITTAB
		for(int i=0;i<LITTAB.size();i++)
		{
			Tables row=LITTAB.get(i);
			System.out.println(i+"\t"+row.getSymbol()+"\t"+row.getAddess());
			bw.write((i+1)+"\t"+row.getSymbol()+"\t"+row.getAddess()+"\n");
		}
		bw.close();
	}
	void printPOOLTAB() throws IOException
	{
		BufferedWriter bw=new BufferedWriter(new FileWriter("POOLTAB.txt"));
		System.out.println("\nPOOLTAB");
		System.out.println("Index\tLitIndex");
		//bw.write("\nPOOLTAB\n");
		//bw.write("Index\t#first\n");
		if(libtab_ptr==0)
		POOLTAB.clear();
		
		for (int i = 0; i < POOLTAB.size(); i++) {
			System.out.println(i+"\t"+POOLTAB.get(i));
			bw.write(i+"\t"+POOLTAB.get(i)+"\n");
		}
		bw.close();
	}
	void printSYMTAB() throws IOException
	{
		BufferedWriter bw=new BufferedWriter(new FileWriter("SYMTAB.txt"));
		//Printing Symbol Table
		java.util.Iterator<String> iterator = SYMTAB.keySet().iterator();
		System.out.println("\nSYMBOL TABLE");
		System.out.println("Index\tSymbol\tAddress");
		//bw.write("\nSYMBOL TABLE\n");
		while (iterator.hasNext()) {
			String key = iterator.next().toString();
			Tables value = SYMTAB.get(key);

			System.out.println(value.getIndex()+"\t" + value.getSymbol()+"\t"+value.getAddess());
			bw.write(value.getIndex()+"\t" + value.getSymbol()+"\t"+value.getAddess()+"\n");
		}
		bw.close();
	}
	public int expr(String str)
	{
		int temp=0;
		if(str.contains("+"))
		{
			String splits[]=str.split("\\+");
			temp=SYMTAB.get(splits[0]).getAddess()+Integer.parseInt(splits[1]);
		}
		else if(str.contains("-"))
		{
			String splits[]=str.split("\\-");
			temp=SYMTAB.get(splits[0]).getAddess()-(Integer.parseInt(splits[1]));
		}
		else
		{
			temp=Integer.parseInt(str);
		}
		return temp;
	}
}


/*Assemblers are tools in computer science that convert assembly language code into machine code, allowing programs to be executed by the computer's hardware. Assemblers operate in two primary passes (Pass1 and Pass2) to generate machine code efficiently and handle macros, labels, and other assembly instructions. Here is an explanation of assemblers and their passes, focusing on the macro processing in both Pass1 and Pass2:

---

### 1. **Assembler Overview**

An assembler takes human-readable assembly code and translates it into machine code. Assembly languages are low-level languages that provide instructions specific to the architecture, acting as an interface between high-level programming languages and machine language.

- **Assembly Language**: Contains mnemonic instructions, labels, directives, and sometimes macros. It's symbolic, making it easier for programmers to use than pure binary.
- **Machine Language**: Binary code that directly controls the hardware. Each assembly instruction maps to one or more machine code instructions.

---

### 2. **Assembler Functions**
Assemblers are responsible for:
1. **Syntax Analysis**: Parsing and verifying assembly instructions.
2. **Symbol Table Management**: Storing addresses of labels and variables.
3. **Macro Processing**: Expanding macros by replacing them with their instructions.
4. **Code Generation**: Translating mnemonic instructions into binary machine code.

---

### 3. **Two-Pass Assembly Process**

Assemblers generally follow a two-pass structure to handle forward references, where labels or macros are defined later in the code but are used earlier. Here’s how Pass1 and Pass2 operate:

---

### 4. **Pass1: Definition and Analysis**

The primary goal of **Pass1** is to process the macro definitions, build tables (like the Macro Name Table (MNT), Argument List Array (ALA), and Macro Definition Table (MDT)), and manage symbol addresses without generating the final machine code.

#### **Process of Pass1:**
1. **Initialize Tables**:
   - **MNT (Macro Name Table)**: Stores the names of macros and their locations in the MDT.
   - **MDT (Macro Definition Table)**: Stores the body of each macro, replacing arguments with formal parameters.
   - **ALA (Argument List Array)**: Maintains formal arguments for each macro, replacing them with placeholders like `#0`, `#1`, etc., to standardize arguments within the MDT.

2. **Macro Parsing**:
   - When the assembler encounters a `MACRO` keyword, it begins processing a macro.
   - It adds the macro name to the MNT along with its MDT location.
   - Each argument is recorded in the ALA with placeholders.

3. **Macro Body Handling**:
   - As the assembler reads the macro body, it replaces actual arguments with placeholders and stores each line in the MDT.
   - The macro body ends with the `MEND` directive, signaling the end of the macro definition in the MDT.

4. **Other Symbols and Labels**:
   - The assembler records labels and symbols, preparing a symbol table to resolve addresses in Pass2.

**Example**:
- If the code contains:
    ```assembly
    MACRO ADDMAC A,B
    LDA A
    ADD B
    MEND
    ```
   The assembler would store the macro `ADDMAC` in the MNT, with `A` and `B` mapped to `#0` and `#1` in the ALA and the respective `LDA #0` and `ADD #1` instructions in the MDT.

---

### 5. **Pass2: Expansion and Code Generation**

In **Pass2**, the assembler:
1. **Expands Macros**: Using MNT and MDT, it expands macro calls encountered in the source code, substituting placeholders in the MDT with actual parameters specified at each macro call.
2. **Generate Machine Code**: For each instruction, it translates mnemonics into machine code, resolves label addresses using the symbol table, and finally produces the machine code for the program.

#### **Process of Pass2**:
1. **Read Assembly Statements**:
   - It begins at the program’s starting point (indicated by `START`).
   - It processes each line and checks if it’s a macro call or an instruction.

2. **Macro Expansion**:
   - If a macro call is encountered, Pass2 retrieves the macro’s body from the MDT and the actual arguments from the ALA.
   - Using the ALA, it replaces the placeholders (`#0`, `#1`, etc.) in the MDT with the actual arguments provided in the call.

3. **Final Code Generation**:
   - The assembler translates each expanded instruction line into machine code, outputting the final machine code for the program.
   - Any remaining labels or variables are resolved using the symbol table.

**Example**:
- Suppose the source code has:
    ```assembly
    ADDMAC X,Y
    ```
   During Pass2, the assembler will expand this call to:
    ```assembly
    LDA X
    ADD Y
    ```

---

### 6. **Example of Pass1 and Pass2 Workflow**

Consider the following assembly code:

```assembly
MACRO INCR A
LOAD A
ADD 1
MEND
START
INCR X
INCR Y
END
```

#### **Pass1**:
- **MNT**:
    - `INCR` with a starting location in the MDT.
- **MDT**:
    - Stores `LOAD #0` and `ADD 1` (replacing `A` with `#0`).
- **ALA**:
    - For `INCR`, `A` is represented as `#0`.

#### **Pass2**:
- Expands `INCR X` to `LOAD X` and `ADD 1`, and similarly `INCR Y` to `LOAD Y` and `ADD 1`.
- Translates instructions to machine code.

---

### 7. **Conclusion**
The two-pass approach ensures efficient code assembly and macro expansion, making it ideal for complex programs where labels and macros are reused. Pass1 focuses on macro and symbol definition, building tables that help streamline Pass2, which handles macro expansion and machine code generation. This modular approach allows assemblers to handle forward references and nested macros, essential for robust assembly language programming.

--- 

This two-pass system exemplifies how assemblers manage macros, labels, and machine code translation systematically. Let me know if you'd like more detailed information on any specific part!*/

/*### Explanation of Pass1 and Pass2 Assembler Code

In the provided code, we have two classes, `Pass1asm` and `Pass2asm`, which represent the Pass 1 and Pass 2 phases of a two-pass assembler. This assembler generates machine code by converting symbolic assembly language instructions into binary/hexadecimal machine code.

### Key Concepts and Working of Each Phase

1. **Pass1asm (Pass 1):**
   - **Goal:** Create an Intermediate Code (IC), Symbol Table (SYMTAB), Literal Table (LITTAB), and Pool Table (POOLTAB).
   - **SYMTAB:** Stores labels (symbolic names) along with their memory addresses.
   - **LITTAB:** Stores literals and their resolved addresses.
   - **POOLTAB:** Keeps track of the literals to handle multiple literal pools if necessary.
   - **Working:** 
     - For each line in the input assembly code:
       - **Labels:** If a label is found, it is stored in SYMTAB with its address.
       - **Directives (e.g., START, END, LTORG):** They manage locations, literals, and program start/end.
       - **Instructions:** Mnemonics are replaced by their respective opcodes from an operation table (OPtable).
       - **Literals:** Encountered literals are added to LITTAB and POOLTAB for resolving in Pass 2.

2. **Pass2asm (Pass 2):**
   - **Goal:** Use IC, SYMTAB, and LITTAB to generate the final machine code.
   - **Working:** 
     - Reads IC, replaces symbolic references (SYMTAB and LITTAB) with actual addresses, and writes the final machine code in `PASS2.txt`.

### Detailed Code Explanation

#### Pass1asm (Pass 1)
1. **Data Structures**:
   - `SYMTAB`: Stores symbols (labels) with address and index.
   - `LITTAB`: Stores literals with index and address.
   - `POOLTAB`: Manages multiple literal pools.

2. **parseFile() Method**:
   - **START** directive initializes the `location counter (lc)`.
   - **ORIGIN** updates `lc` based on expressions.
   - **EQU** directive equates a label to another label/address.
   - **LTORG** & **END** handle literals by assigning addresses to literals in the current literal pool.
   - **DC** and **DS** handle data constants and storage reservation.
   - **Imperative Statements** (using OPtable for mnemonic lookup): Generates the intermediate code.

3. **File Outputs**:
   - `IC.txt`: Stores intermediate code.
   - `SYMTAB.txt`, `LITTAB.txt`, `POOLTAB.txt`: Store respective tables for Pass 2.

#### Pass2asm (Pass 2)
1. **readtables() Method**:
   - Loads SYMTAB and LITTAB generated by Pass 1.

2. **generateCode() Method**:
   - **Imperative Statements** (IS): Converts intermediate statements to machine code by replacing symbols and literals with their actual addresses.
   - **Declarative Statements (DL)**: Outputs constant data in machine code format.

3. **printMC() Method**:
   - Displays generated machine code.

### Possible Viva Questions

1. **What is the purpose of a two-pass assembler?**
   - The two-pass assembler separates symbol and literal table generation (Pass 1) from final code generation (Pass 2), ensuring that all symbols and literals are resolved before machine code generation.

2. **Explain the role of SYMTAB and LITTAB in assembly language processing.**
   - SYMTAB stores the addresses of labels or symbols, while LITTAB holds literals and their assigned memory addresses.

3. **Why is the POOLTAB used, and what is its significance?**
   - POOLTAB manages the allocation of literals across different literal pools, which is important when instructions like `LTORG` force literal resolution at different program locations.

4. **How does the assembler handle different instruction types like IS, AD, and DL?**
   - **IS (Imperative Statements):** Represents actual instructions to be converted to machine code.
   - **AD (Assembler Directives):** These are instructions for the assembler, like setting start points or handling literals.
   - **DL (Declarative Statements):** Reserves memory or declares constants.

5. **What is the purpose of the `expr()` function in Pass1asm?**
   - It evaluates expressions for `ORIGIN` and `EQU` directives, helping update the `lc` based on the expression's result.

6. **How does Pass 2 use the tables created in Pass 1?**
   - Pass 2 reads SYMTAB and LITTAB to replace symbolic references in the intermediate code with actual addresses to produce the final machine code.

7. **What happens if an undefined symbol is encountered in Pass 2?**
   - Normally, an assembler would throw an error for undefined symbols. Here, the code assumes all symbols are defined in Pass 1.

### Example Execution Flow (For Clarification)
Suppose the input code contains labels, literals, and instructions. The assembler will:
   - **Pass 1:** Identify labels, store literals, and produce intermediate code.
   - **Pass 2:** Convert the intermediate code to final machine code by resolving all symbols and literals. 

This process exemplifies the two-pass assembly process, where Pass 1 gathers data, and Pass 2 generates the final machine code.*/
