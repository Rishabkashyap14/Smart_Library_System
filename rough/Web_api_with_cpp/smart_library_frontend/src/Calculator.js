import React from 'react'
import CalculatorPanel from './CalculatorPanel'
	
class Calculator extends React.Component
{
	constructor(props)
	{
		super(propr);
		this.state = {
				result = "",
				numbers: ["", ""],
				numberIndex: 0,
				operation: "",
		};
	}	
	
	//Handling Operations when encountered
	operationHandler(operation)
	{
		if(this.state.numberIdx = 1)
		{
			this.equalHandler(); 
			return;
		}
		if((operation == "subtract" || operation == "add") && (this.state.numbers[this.state.numberIdx] === "")
		{
			this.numberHandler(operation === "subtract" ? "-":"+");
			return;
		}
		
	}
	
	//Updating operation in the state variable
	setOperation(operation)
	{
		this.setState({
			operation: operation
		});
		
	}
	
	//Handling numbers
	numberHandler(number)
	{
		const newNumber = this.state.numbers[this.state.numberIdx] + number;
		this.updateNumber(newNumber);
	}
	
	//Update the number array in the state object
	updateNumber(newNumber)
	{
		var newNumbers = this.state.numbers;
		newNumbers[this.state.numberIdx] = newNumber;
		this.setState({
			result: newNumbers[this.state.numberIdx],
			numbers: newNumbers,
		});
	}

	dotHandler()
	{
		const newNumber = this.state.numbers[this.state.numberIdx] + ".";
		if(isNaN(newNumber))
		{
			return;
		}
		this.updateNumber(newNumber);
	}

	clearHandler()
	{
	}

	equalHandler()
	{
	}

	render(){
		return(
			<div className="calculator-grid-container">
				<CalculatorPanel
					result={this.state.result}
					numberClicked={this.numberHandler.bind(this)}
					operationClicked={this.operationHandler.bind(this)}
					dotClicked={this.dotHandler.bind(this)}
					equalHandler={this.equalHandler.bind(this)}
					clearHandler={this.clearHandler.bind(this)}
				/>
			</div>
		);
	}

}

export default Calculator;
