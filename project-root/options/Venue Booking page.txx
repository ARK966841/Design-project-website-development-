import { useState } from "react";
import { useBookingForm } from "@/hooks/use-booking-form";
import { Button } from "@/components/ui/button";
import { toast } from "@/hooks/use-toast";
import FormStepper from "./FormStepper";
import PersonalInfoStep from "./steps/PersonalInfoStep";
import EventDetailsStep from "./steps/EventDetailsStep";
import VenuePreferencesStep from "./steps/VenuePreferencesStep";
import ServicesStep from "./steps/ServicesStep";
import AdditionalInfoStep from "./steps/AdditionalInfoStep";
import ConfirmationStep from "./steps/ConfirmationStep";

interface VenueBookingFormProps {
  onSubmitSuccess: (data: any) => void;
}

export default function VenueBookingForm({ onSubmitSuccess }: VenueBookingFormProps) {
  const { currentStep, setCurrentStep, formData, steps } = useBookingForm();
  const [validationErrors, setValidationErrors] = useState<Record<string, string>>({});

  const validateCurrentStep = () => {
    const errors: Record<string, string> = {};
    let isValid = true;

    // Personal Info validation
    if (currentStep === 0) {
      if (!formData.fullName?.trim()) {
        errors.fullName = "Full name is required";
        isValid = false;
      }
      
      if (!formData.email?.trim()) {
        errors.email = "Email is required";
        isValid = false;
      } else if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(formData.email)) {
        errors.email = "Valid email address is required";
        isValid = false;
      }
      
      if (!formData.phone?.trim()) {
        errors.phone = "Phone number is required";
        isValid = false;
      }
    }
    
    // Event Details validation
    if (currentStep === 1) {
      if (!formData.eventType?.trim()) {
        errors.eventType = "Event type is required";
        isValid = false;
      }
      
      if (!formData.eventDate?.trim()) {
        errors.eventDate = "Event date is required";
        isValid = false;
      }
      
      if (!formData.guests?.trim()) {
        errors.guests = "Number of guests is required";
        isValid = false;
      }
    }
    
    // Confirmation step validation
    if (currentStep === 5) {
      if (!formData.agreeTerms) {
        errors.agreeTerms = "You must agree to the terms and conditions";
        isValid = false;
      }
      
      if (!formData.agreeCancel) {
        errors.agreeCancel = "You must acknowledge the cancellation policy";
        isValid = false;
      }
    }

    setValidationErrors(errors);
    return isValid;
  };

  const handleNext = () => {
    if (validateCurrentStep()) {
      if (currentStep < steps.length - 1) {
        setCurrentStep(currentStep + 1);
        window.scrollTo(0, 0);
      }
    } else {
      toast({
        title: "Please check the form",
        description: "Some required fields need your attention",
        variant: "destructive",
      });
    }
  };

  const handlePrevious = () => {
    if (currentStep > 0) {
      setCurrentStep(currentStep - 1);
      window.scrollTo(0, 0);
    }
  };

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    
    if (validateCurrentStep()) {
      console.log("Final form data:", formData);
      toast({
        title: "Booking submitted!",
        description: "Your venue booking has been submitted successfully.",
      });
      onSubmitSuccess(formData);
    }
  };

  const renderStep = () => {
    switch (currentStep) {
      case 0:
        return <PersonalInfoStep validationErrors={validationErrors} />;
      case 1:
        return <EventDetailsStep validationErrors={validationErrors} />;
      case 2:
        return <VenuePreferencesStep validationErrors={validationErrors} />;
      case 3:
        return <ServicesStep validationErrors={validationErrors} />;
      case 4:
        return <AdditionalInfoStep validationErrors={validationErrors} />;
      case 5:
        return <ConfirmationStep validationErrors={validationErrors} />;
      default:
        return null;
    }
  };

  return (
    <form onSubmit={handleSubmit} className="animate-fade-in">
      <FormStepper />
      
      <div className="p-6 md:p-8">
        {renderStep()}
        
        <div className="flex justify-between mt-8 pt-4 border-t">
          <Button
            type="button"
            variant="outline"
            onClick={handlePrevious}
            disabled={currentStep === 0}
          >
            Previous
          </Button>
          
          {currentStep < steps.length - 1 ? (
            <Button type="button" onClick={handleNext}>
              Next Step
            </Button>
          ) : (
            <Button type="submit" className="bg-gradient-to-r from-green-600 to-emerald-600 hover:from-green-700 hover:to-emerald-700">
              Submit Booking
            </Button>
          )}
        </div>
      </div>
    </form>
  );
}